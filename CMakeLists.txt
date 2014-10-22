project(arch-arm-cross)

## Setup
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CMakeCMacros)
include(GNUInstallDirs)

cmake_c_add_flags(CMAKE_C_FLAGS -Wall -Wextra -std=gnu11 -D_GNU_SOURCE)
cmake_c_add_flags(CMAKE_CXX_FLAGS -Wall -Wextra
  -Wno-deprecated-register -std=c++11 -D_GNU_SOURCE)
cmake_c_add_flags(CMAKE_SHARED_LINKER_FLAGS -Wl,--as-needed -Wl,--no-undefined)
cmake_c_add_flags(CMAKE_MODULE_LINKER_FLAGS -Wl,--as-needed -Wl,--no-undefined)

set(ARCH_ARM_LIBEXEC
  "${CMAKE_INSTALL_FULL_LIBDIR}/arch-arm-cross/${CMAKE_SYSTEM_PROCESSOR}")

add_subdirectory(data)
add_subdirectory(qemu-wrapper)
add_subdirectory(scripts)
