set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_SYSROOT /usr/lib/arch-arm-cross/pkg_root/armv8/)
set(CMAKE_STAGING_PREFIX /usr/lib/arch-arm-cross/pkg_root/armv8/)

set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
