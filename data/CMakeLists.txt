configure_file(pacman-arm.conf.in pacman-arm.conf @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pacman-arm.conf" makepkg-arm.conf
  DESTINATION "${CMAKE_INSTALL_DATADIR}/arch-arm-cross")
install(FILES mirrorlist
  RENAME mirrorlist-arm-cross
  DESTINATION "${CMAKE_INSTALL_SYSCONFDIR}/pacman.d")
install(FILES ARMv7hf.cmake
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/Modules/")
