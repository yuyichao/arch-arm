/* Copyright (C) 2014~2015 by Yichao Yu
 * yyc1992@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

#include <string>
#include <vector>

extern char **environ;

class QemuCommand {
    const std::string m_conf_file;
    char *m_cmd_str;
    size_t m_cmd_len;

    void set_cmd(const char *cmd, size_t size=0);
    void try_mmap();
public:
    inline QemuCommand(const std::string &exe_dir, bool arm64);
    inline ~QemuCommand();

    int exec(int argc, char *argv[]);
};

void
QemuCommand::set_cmd(const char *cmd, size_t size)
{
    if (!size) {
        size = strlen(cmd) + 1;
    }
    m_cmd_str = (char*)realloc(m_cmd_str, size + 1);
    m_cmd_len = size;
    memcpy(m_cmd_str, cmd, size);
    m_cmd_str[size] = '\0';
    if (m_cmd_str[size - 1]) {
        m_cmd_len++;
    }
}

void
QemuCommand::try_mmap()
{
    int fd = open(m_conf_file.c_str(), O_RDONLY | O_CLOEXEC);
    if (fd == -1)
        return;
    struct stat buf;
    if (fstat(fd, &buf) == -1) {
        close(fd);
        return;
    }
    void *map = mmap(nullptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (map == (void*)-1) {
        return;
    }
    set_cmd((char*)map, buf.st_size);
    munmap(map, buf.st_size);
}

inline
QemuCommand::QemuCommand(const std::string &exe_dir, bool arm64)
    : m_conf_file(exe_dir + (arm64 ? "/qemu_cmd_aarch64" : "/qemu_cmd_arm")),
      m_cmd_str(nullptr), m_cmd_len(0)
{
    try_mmap();
    if (!m_cmd_str) {
        // TODO set at config time or find at run time.
        set_cmd(arm64 ? "/usr/bin/qemu-arm" : "/usr/bin/qemu-aarch64");
    }
}

inline
QemuCommand::~QemuCommand()
{
    free(m_cmd_str);
}

int
QemuCommand::exec(int argc, char *argv[])
{
    std::vector<const char*> cmd;
    char *cmd_end = m_cmd_str + m_cmd_len;
    for (char *cur_arg = m_cmd_str;cur_arg < cmd_end;
         cur_arg += strlen(cur_arg) + 1) {
        cmd.push_back(cur_arg);
    }
    std::vector<char*> envp = {};
    for (char **env = environ;*env;env++) {
        if (!strchr(*env, ',') && strchr(*env, '=')) {
            cmd.push_back("-E");
            cmd.push_back(*env);
        } else {
            // QEMU cannot handle environment variable with "," or "=" in it
            // Hopefully these are not one of the envs that the dynamic linker
            // will response to. (e.g. LD_TRACE_LOADED_OBJECTS)
            envp.push_back(*env);
        }
    }
    cmd.push_back("-0");
    cmd.push_back(argv[2]);
    cmd.push_back(argv[1]);
    for (int i = 3;i < argc;i++) {
        cmd.push_back(argv[i]);
    }
    // for (unsigned i = 0;i < cmd.size();i++) {
    //     printf("arg[%d] = '%s'\n", i, cmd[i]);
    // }
    cmd.push_back(nullptr);
    envp.push_back(nullptr);
    execve(cmd[0], const_cast<char* const*>(&cmd[0]), &envp[0]);
    return errno;
}

int
main(int argc, char *argv[])
{
    char *exe_path = realpath(argv[0], NULL);
    std::string exe_dir = dirname(exe_path);
    free(exe_path);
    bool arm64 = false;
    if (size_t arglen = strlen(argv[0])) {
        const auto suffix_len = strlen("-aarch64");
        arm64 = arglen > suffix_len && memcmp(argv[0] + arglen - suffix_len,
                                              "-aarch64", suffix_len) == 0;
    }
    QemuCommand qemu_cmd(exe_dir, arm64);
    return qemu_cmd.exec(argc, argv);
}
