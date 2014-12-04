project(arch-arm-cross)

## Setup
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CMakeCMacros)
include(GNUInstallDirs)

cmake_c_add_flags(CMAKE_C_FLAGS -Wall -Wextra -std=gnu11 -D_GNU_SOURCE -flto)
cmake_c_add_flags(CMAKE_CXX_FLAGS -Wall -Wextra
  -Wno-deprecated-register -std=c++11 -D_GNU_SOURCE -flto)
cmake_c_add_flags(CMAKE_SHARED_LINKER_FLAGS -Wl,--as-needed
  -Wl,--no-undefined -flto)
cmake_c_add_flags(CMAKE_MODULE_LINKER_FLAGS -Wl,--as-needed
  -Wl,--no-undefined -flto)
cmake_c_add_flags(CMAKE_EXE_LINKER_FLAGS -Wl,--as-needed
  -Wl,--no-undefined -flto)

set(ARCH_ARM_SCRIPTS "${CMAKE_INSTALL_FULL_LIBDIR}/arch-arm-cross")
set(ARCH_ARM_LIBEXEC "${ARCH_ARM_SCRIPTS}/${CMAKE_SYSTEM_PROCESSOR}")

add_subdirectory(data)
add_subdirectory(qemu-wrapper)
add_subdirectory(scripts)
