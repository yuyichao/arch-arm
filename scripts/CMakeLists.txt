set(SYSROOT /usr/arm-linux-gnueabihf/)
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd"
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/write-cmd"
  "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd" /usr/bin/qemu-arm -L "${SYSROOT}")
add_custom_target(qemu-cmd-conf ALL
  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd")

configure_file(prepare-qemu.in prepare-qemu @ONLY)
configure_file(prepare-chroot.in prepare-chroot @ONLY)
configure_file(pacman-arm-cross.in pacman-arm-cross @ONLY)
configure_file(makepkg-arm-cross.in makepkg-arm-cross @ONLY)

install(FILES write-cmd
  DESTINATION "${ARCH_ARM_SCRIPTS}"
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/prepare-qemu"
   "${CMAKE_CURRENT_BINARY_DIR}/prepare-chroot"
  DESTINATION "${ARCH_ARM_LIBEXEC}"
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pacman-arm-cross"
  "${CMAKE_CURRENT_BINARY_DIR}/makepkg-arm-cross"
  DESTINATION "${CMAKE_INSTALL_BINDIR}"
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/qemu_cmd"
  DESTINATION "${ARCH_ARM_LIBEXEC}")
