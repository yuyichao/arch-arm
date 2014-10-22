set(SRCS
  wrapper.cpp)

set(exe_name arch-arm-qemu)

add_executable(${exe_name} ${SRCS})

# target_link_libraries(${exe_name})

install(TARGETS ${exe_name} DESTINATION "${ARCH_ARM_LIBEXEC}")
