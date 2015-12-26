set(SRCS
  wrapper.cpp)

set(exe_name arch-qemu-arm)

add_executable(${exe_name} ${SRCS})
set_target_properties(${exe_name} PROPERTIES
  LINK_FLAGS "-static-libgcc -static-libstdc++ -static")

install(TARGETS ${exe_name} DESTINATION "${ARCH_ARM_LIBEXEC}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${exe_name}"
  DESTINATION "${ARCH_ARM_LIBEXEC}"
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  RENAME arch-qemu-aarch64)
