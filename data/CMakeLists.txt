configure_file(pacman-arm.conf.in pacman-arm.conf @ONLY)
configure_file(makepkg-arm.conf.in makepkg-arm.conf @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pacman-arm.conf"
  "${CMAKE_CURRENT_BINARY_DIR}/makepkg-arm.conf"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/arch-arm-cross")
install(FILES mirrorlist
  RENAME mirrorlist-arm-cross
  DESTINATION "${CMAKE_INSTALL_SYSCONFDIR}/pacman.d")

install(FILES
  cmake/ARMv7hf.cmake cmake/ARMv7hf-Clang.cmake
  cmake/ARMv8.cmake cmake/ARMv8-Clang.cmake
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/Modules/")
