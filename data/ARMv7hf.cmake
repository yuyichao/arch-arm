set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_SYSROOT /usr/arm-linux-gnueabihf/pkg_root/)
set(CMAKE_STAGING_PREFIX /usr/arm-linux-gnueabihf/pkg_root/)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
