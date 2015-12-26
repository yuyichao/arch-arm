set(SYSROOT_ARM /usr/arm-linux-gnueabihf/)
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd_arm"
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/write-cmd"
  "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd_arm" /usr/bin/qemu-arm -L "${SYSROOT_ARM}"
  -E "LD_LIBRARY_PATH=/usr/lib/arch-arm-cross/pkg_root/armv7/usr/lib")
add_custom_target(qemu-cmd-arm-conf ALL
  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd_arm")

set(SYSROOT_AARCH64 /usr/aarch-linux-gnu/)
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd_aarch64"
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/write-cmd"
  "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd_aarch64"
  /usr/bin/qemu-aarch64 -L "${SYSROOT_AARCH64}"
  -E "LD_LIBRARY_PATH=/usr/lib/arch-arm-cross/pkg_root/armv8/usr/lib")
add_custom_target(qemu-cmd-aarch64-conf ALL
  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd_aarch64")

configure_file(arch-arm-cross-config.sh.in arch-arm-cross-config.sh @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/arch-arm-cross-config.sh"
  DESTINATION "${CMAKE_INSTALL_BINDIR}")

set(exec_perm OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

function(install_bin_exec file rename)
  install(FILES "${file}" DESTINATION "${CMAKE_INSTALL_BINDIR}"
    RENAME "${rename}"
    PERMISSIONS ${exec_perm})
endfunction()

install(FILES write-cmd
  DESTINATION "${ARCH_ARM_SCRIPTS}"
  PERMISSIONS ${exec_perm})

install(FILES prepare-qemu-arm prepare-qemu-aarch64 prepare-chroot
  DESTINATION "${ARCH_ARM_LIBEXEC}"
  PERMISSIONS ${exec_perm})

install(FILES pacman-arm-cross
  DESTINATION "${CMAKE_INSTALL_BINDIR}"
  PERMISSIONS ${exec_perm})

install_bin_exec(makepkg-arm-cross makepkg-armv7)
install_bin_exec(makepkg-arm-cross makepkg-armv8)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd_arm"
  "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd_aarch64"
  DESTINATION "${ARCH_ARM_LIBEXEC}")
