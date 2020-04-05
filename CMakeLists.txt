cmake_minimum_required(VERSION 3.12)

project(PidToolkit VERSION 1.0.0.0
  DESCRIPTION "GOS PID Toolkit"
  LANGUAGES C CXX)
  
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

option(GOS_PID_TOOLKIT_C "Build C version of PID Toolkit" OFF)
option(GOS_PID_TOOLKIT_CPP "Build C++ version of PID Toolkit" ON)
option(GOS_PID_TOOLKIT_TEST "Build and execute the unit tests" OFF)
option(GOS_PID_ARDUINO_BASED_TUNING "Build the Arduino Based auto-tuning" ON)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

option(CLANG_TIDY "Perform Clang-Tidy check" OFF)

if (CLANG_TIDY)
  option(CLANG_TIDY_FIX_ERRORS
    "Perform fixes with Clang-Tidy even if compilation errors were found" OFF)
  option(CLANG_TIDY_FIX "Perform fixes with Clang-Tidy" OFF)
  set(TIDY_ARGUMENTS "-checks=*,-clang-analyzer-alpha.* "
    CACHE STRING "Arguments for Clang-Tidy check")
  set(TIDY_FIX_ARGUMENTS "-list-checks=*,-clang-analyzer-alpha.* "
    CACHE STRING "Arguments for Clang-Tidy fix")
  set(TIDY_FIX_ERRORS_ARGUMENTS "-checks=*,-clang-analyzer-alpha.* "
    CACHE STRING "Arguments for Clang-Tidy fix errors")
  find_program(CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable")
  if(CLANG_TIDY_EXE)
    if(CLANG_TIDY_FIX_ERRORS)
      set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}" "${TIDY_FIX_ERRORS_ARGUMENTS}-fix-errors")
      message(STATUS "Using clang-tidy with fix")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_FIX_ERRORS_ARGUMENTS}-fix-errors")
    elseif(CLANG_TIDY_FIX)
      set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "${TIDY_FIX_ARGUMENTS}-fix")
      message(STATUS "Using clang-tidy with fix")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_FIX_ARGUMENTS}-fix")
    else()
      set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}" "${TIDY_ARGUMENTS}")
      message(STATUS "Using clang-tidy")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_ARGUMENTS}")
    endif()
  endif()
endif (CLANG_TIDY)

if (GOS_PID_TOOLKIT_C)
  set(gos_pid_toolkit_c_include_dir
    "${CMAKE_CURRENT_SOURCE_DIR}/include/c")
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/c/gos/pid/toolkit/version.h.in"
    "include/c/gos/pid/toolkit/version.h"
    @ONLY)
  set(gos_pid_toolkit_c_version_include_file
    "${CMAKE_CURRENT_BINARY_DIR}/include/c/gos/pid/toolkit/version.h")
  set(gos_pid_toolkit_c_binary_include
    "${CMAKE_CURRENT_BINARY_DIR}/include/c")
endif (GOS_PID_TOOLKIT_C)

if (GOS_PID_TOOLKIT_CPP)
  set(gos_pid_toolkit_cpp_include_dir
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp")
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/version.h.in"
    "include/cpp/gos/pid/toolkit/version.h"
    @ONLY)
  set(gos_pid_toolkit_cpp_version_include_file
    "${CMAKE_CURRENT_BINARY_DIR}/include/cpp/gos/pid/toolkit/version.h")
  set(gos_pid_toolkit_cpp_binary_include_dir
    "${CMAKE_CURRENT_BINARY_DIR}/include/cpp")
  list(APPEND gos_pid_toolkit_cpp_public_header
    "${gos_pid_toolkit_cpp_version_include_file}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/exception.h")
  list(APPEND gos_pid_toolkit_cpp_include
    "${gos_pid_toolkit_cpp_include_dir}"
    "${gos_pid_toolkit_cpp_binary_include_dir}")
  set(gos_pid_toolkit_cpp_library_target libpidtoolkitcpp)
  set(gos_build_dependency_boost ON)
endif (GOS_PID_TOOLKIT_CPP)

if (GOS_PID_ARDUINO_BASED_TUNING)
  set(gos_pid_arduino_based_include_dir
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp")
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/version.h.in"
    "include/cpp/gos/pid/arduino/autotuning/version.h"
    @ONLY)
  set(gos_pid_arduino_based_version_include_file
    "${CMAKE_CURRENT_BINARY_DIR}/include/cpp/gos/pid/arduino/autotuning/version.h")
  set(gos_pid_arduino_based_binary_include_dir
    "${CMAKE_CURRENT_BINARY_DIR}/include/cpp")
  list(APPEND gos_pid_arduino_based_public_header
    "${gos_pid_arduino_based_version_include_file}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/arduinobasedautotuning.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/arduinobasedautotuninglibrary.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/arrayvariables.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/framework.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/input.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/output.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/parameters.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/pch.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/type.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/autotuning/variables.h")
  list(APPEND gos_pid_arduino_based_include
    "${gos_pid_arduino_based_include_dir}"
    "${gos_pid_arduino_based_binary_include_dir}")
  set(gos_pid_arduino_based_library_target libarduinobasedautotuning)
endif (GOS_PID_ARDUINO_BASED_TUNING)

if (gos_build_dependency_boost)
  set(Boost_USE_MULTITHREADED        ON)
  set(Boost_USE_STATIC_RUNTIME      OFF)
  if (BUILD_SHARED_LIBS)
    set(Boost_USE_STATIC_LIBS       OFF)    
  else ()
    set(Boost_USE_STATIC_LIBS        ON)
  endif ()

  list(APPEND gos_pid_toolkit_boost_package
#   system
#   date_time
#   filesystem
    serialization)
 list(REMOVE_DUPLICATES gos_pid_toolkit_boost_package)

  if (gos_pid_toolkit_boost_package)
    find_package(Boost 1.71 COMPONENTS REQUIRED
      ${gos_pid_toolkit_boost_package})
  else ()
    find_package(Boost 1.71)
  endif ()

# if (GOS_PID_TOOLKIT_CPP)
#   list(APPEND gos_pid_toolkit_cpp_include
#     ${Boost_INCLUDE_DIRS})
# endif (GOS_PID_TOOLKIT_CPP)
endif ()

if (GOS_PID_TOOLKIT_C)
  add_subdirectory(src/c)
endif (GOS_PID_TOOLKIT_C)

add_subdirectory(src/cpp)

if (GOS_PID_TOOLKIT_TEST)
  if (MSVC)
    #if (NOV_FORCE_SHARED_CRT)
      set(gtest_force_shared_crt ON CACHE BOOL "Use Shared CRT")
    #endif ()
  endif (MSVC)
  if (GOS_PID_TOOLKIT_INSTRUCT_GOOGLE_TEST_PATH)
    set(GOS_PID_TOOLKIT_GOOGLE_TEST_PATH
      "${GOS_PID_TOOLKIT_INSTRUCT_GOOGLE_TEST_PATH}")
  else ()
    set(GOS_PID_TOOLKIT_GOOGLE_TEST_PATH
      "${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest")
    add_subdirectory(extern/googletest)
  endif ()
  set(gos_pid_toolkit_unit_testing_dir
    "${CMAKE_CURRENT_SOURCE_DIR}/tests")
  set(gos_pid_toolkit_unit_testing_gmock_include_dir
    "${GOS_PID_TOOLKIT_GOOGLE_TEST_PATH}/googlemock/include")
  set(gos_pid_toolkit_unit_testing_gtest_include_dir
    "${GOS_PID_TOOLKIT_GOOGLE_TEST_PATH}/googletest/include")
  enable_testing()
  list(APPEND gos_pid_toolkit_gtest_libraries
    gtest
    gmock
    gmock_main)
  if (GOS_PID_TOOLKIT_C)
    add_subdirectory(tests/c)
  endif (GOS_PID_TOOLKIT_C)
  if (GOS_PID_TOOLKIT_CPP)
    add_subdirectory(tests/cpp)
  endif (GOS_PID_TOOLKIT_CPP)
endif (GOS_PID_TOOLKIT_TEST)

message(STATUS "")
message(STATUS "PID Toolkit BUILD SUMMARY")
message(STATUS "  CMAKE_SYSTEM_NAME    : ${CMAKE_SYSTEM_NAME}")
message(STATUS "  CMAKE_GENERATOR      : ${CMAKE_GENERATOR}")
message(STATUS "  CMAKE_MODULE_PATH    : ${CMAKE_MODULE_PATH}")
if (GOS_PID_TOOLKIT_C)
message(STATUS "  C Compiler ID        : ${CMAKE_C_COMPILER_ID}")
endif ()
if (GOS_PID_TOOLKIT_CPP)
message(STATUS "  C++ Compiler ID      : ${CMAKE_CXX_COMPILER_ID}")
endif ()
message(STATUS "  Build type           : ${CMAKE_BUILD_TYPE}")
if (gos_build_dependency_boost)
message(STATUS "  Boost version        : ${Boost_VERSION}")
message(STATUS "  Boost include dir    : ${Boost_INCLUDE_DIRS}")
endif ()
if (GOS_PID_TOOLKIT_TEST)
message(STATUS "  Google Test dir      : ${GOS_PID_TOOLKIT_GOOGLE_TEST_PATH}")
message(STATUS "  Force Shared CRT     : ${gtest_force_shared_crt}")
message(STATUS "  Build and execute unit tests")
endif ()
message(STATUS "")
