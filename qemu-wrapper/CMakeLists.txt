set(SRCS
  wrapper.cpp)

set(exe_name arch-arm-qemu)

add_executable(${exe_name} ${SRCS})
set_target_properties(${exe_name} PROPERTIES
  LINK_FLAGS "-static-libgcc -static-libstdc++ -static")

install(TARGETS ${exe_name} DESTINATION "${ARCH_ARM_LIBEXEC}")
