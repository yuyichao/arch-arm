set(SRCS
  wrapper.cpp)

set(exe_name arch-arm-qemu)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
add_executable(${exe_name} ${SRCS})

# target_link_libraries(${exe_name})

install(TARGETS ${exe_name} DESTINATION "${ARCH_ARM_LIBEXEC}")
