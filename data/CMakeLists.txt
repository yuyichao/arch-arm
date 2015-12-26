configure_file(pacman-arm-options.conf.in pacman-arm-options.conf @ONLY)
configure_file(pacman-armv7.conf.in pacman-armv7.conf @ONLY)
configure_file(pacman-armv8.conf.in pacman-armv8.conf @ONLY)
configure_file(makepkg-arm.conf.in makepkg-arm.conf @ONLY)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/pacman-arm-options.conf"
  "${CMAKE_CURRENT_BINARY_DIR}/pacman-armv7.conf"
  "${CMAKE_CURRENT_BINARY_DIR}/pacman-armv8.conf"
  "${CMAKE_CURRENT_BINARY_DIR}/makepkg-arm.conf"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/arch-arm-cross")
install(FILES mirrorlist
  RENAME mirrorlist-arm-cross
  DESTINATION "${CMAKE_INSTALL_SYSCONFDIR}/pacman.d")

install(FILES
  cmake/ARMv7hf.cmake cmake/ARMv7hf-Clang.cmake
  cmake/ARMv8.cmake cmake/ARMv8-Clang.cmake
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/Modules/")
