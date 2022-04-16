cmake_minimum_required(VERSION 3.0)
project(cborg VERSION 0.1.0 LANGUAGES C)

# BUILD
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -pedantic")

# Include module
include(GNUInstallDirs)

# CBORG
file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/src/*.c")
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(cborg ${SRC})

# INSTALL CBORG
install(TARGETS cborg DESTINATION ${CMAKE_INSTALL_BINDIR})

# UNINSTALL
# source: https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#can-i-do-make-uninstall-with-cmake
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
