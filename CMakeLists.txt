cmake_minimum_required(VERSION 3.0)

project(cborg VERSION 0.5.0 LANGUAGES C) # x-release-please-version
configure_file(${CMAKE_SOURCE_DIR}/include/version.h.in ${CMAKE_BINARY_DIR}/include/version.h @ONLY)

project(cborg-cli VERSION 0.5.0 LANGUAGES C) # x-release-please-version
configure_file(${CMAKE_SOURCE_DIR}/include/cli/cb_cli_version.h.in ${CMAKE_BINARY_DIR}/include/cli/cb_cli_version.h @ONLY)

# BUILD
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -pedantic")
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    add_definitions(-DIS_BIG_ENDIAN)
endif()

# Include module
include(GNUInstallDirs)

# CBORG
file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/src/**.c")

set(SRC_SERVER ${SRC})
set(SRC_CLI ${SRC})

list(REMOVE_ITEM SRC_SERVER "${CMAKE_SOURCE_DIR}/src/cli/cborg-cli.c" "${CMAKE_SOURCE_DIR}/src/cli/cb_cli_opt.c")
list(REMOVE_ITEM SRC_CLI "${CMAKE_SOURCE_DIR}/src/cborg.c" "${CMAKE_SOURCE_DIR}/src/cb_opt.c")

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
add_executable(cborg ${SRC_SERVER})
add_executable(cborg-cli ${SRC_CLI})

# TESTS
include(CTest)
add_executable(test_fs "${CMAKE_SOURCE_DIR}/tests/test_fs.c" "${CMAKE_SOURCE_DIR}/src/cb_fs.c")
add_test(NAME test_fs COMMAND test_fs)
add_executable(test_endianness "${CMAKE_SOURCE_DIR}/tests/test_endianness.c" "${CMAKE_SOURCE_DIR}/src/cb_endianness.c")
add_test(NAME test_endianness COMMAND test_endianness)
add_executable(test_cb_cbor_int "${CMAKE_SOURCE_DIR}/tests/cbor/test_cb_cbor_int.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor_int.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor.c" "${CMAKE_SOURCE_DIR}/src/cb_endianness.c")
add_test(NAME test_cb_cbor_int COMMAND test_cb_cbor_int)
add_executable(test_cb_cbor_simple "${CMAKE_SOURCE_DIR}/tests/cbor/test_cb_cbor_simple.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor_simple.c")
add_test(NAME test_cb_cbor_simple COMMAND test_cb_cbor_simple)
add_executable(test_cb_ops "${CMAKE_SOURCE_DIR}/tests/test_cb_ops.c" "${CMAKE_SOURCE_DIR}/src/cb_ops.c" "${CMAKE_SOURCE_DIR}/src/cb_endianness.c" "${CMAKE_SOURCE_DIR}/src/cb_fs.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor_int.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor_simple.c")
add_test(NAME test_cb_ops COMMAND test_cb_ops)
add_executable(test_cb_cbor_string "${CMAKE_SOURCE_DIR}/tests/cbor/test_cb_cbor_string.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor_string.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor_int.c" "${CMAKE_SOURCE_DIR}/src/cbor/cb_cbor.c" "${CMAKE_SOURCE_DIR}/src/cb_endianness.c")
add_test(NAME test_cb_cbor_string COMMAND test_cb_cbor_string)

# INSTALL CBORG
install(TARGETS cborg DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS cborg-cli DESTINATION ${CMAKE_INSTALL_BINDIR})

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
