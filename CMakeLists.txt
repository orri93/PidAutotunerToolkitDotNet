cmake_minimum_required(VERSION 3.12)

project(PidToolkit VERSION 1.0.0.0
  DESCRIPTION "GOS PID Toolkit"
  LANGUAGES C CXX)
  
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

option(GOS_DEPLOY_PDB_FILES "Deploy PDB files" OFF)

option(GOS_PID_TOOLKIT_C "Build C version of PID Toolkit" OFF)
option(GOS_PID_TOOLKIT_CPP "Build C++ version of PID Toolkit" ON)
option(GOS_PID_TOOLKIT_TEST "Build and execute the unit tests" OFF)
option(GOS_PID_TOOLKIT_UI "Build PID Toolkit UI components" OFF)
option(GOS_PID_ARDUINO_BASED_TUNING "Build the Arduino Based auto-tuning" OFF)
option(GOS_PID_TOOLKIT_INSTALL_CONFIGURATION "Install the configuration file with the target" OFF)
option(GOS_PID_TOOLKIT_INSTALL_DEPENDENCIES "Install runtime dependencies" OFF)
option(GOS_PID_TOOLKIT_EXTERNAL_PROJECT "Add some dependencies as External Project" OFF)

option(BUILD_DOCS "Generate Doxygen" OFF)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

option(CLANG_TIDY "Perform Clang-Tidy check" OFF)

set(gos_pid_toolkit_binary_root ${CMAKE_CURRENT_BINARY_DIR})
set(gos_pid_toolkit_cpp_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

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

set(gos_pid_toolkit_lib_modbus_lib libmodbus)
if (GOS_PID_TOOLKIT_INSTRUCT_LIB_MODBUS_PATH)
  set(gos_pid_toolkit_lib_modbus_path
    "${GOS_PID_TOOLKIT_INSTRUCT_LIB_MODBUS_PATH}")
else ()
  set(gos_pid_toolkit_lib_modbus_path
    "${CMAKE_CURRENT_SOURCE_DIR}/extern/libmodbus")
  if (GOS_PID_TOOLKIT_EXTERNAL_PROJECT)
    include(modbus)
    message(STATUS "")
    message(STATUS "PID Toolkit Modbus Library BUILD SUMMARY")
    message(STATUS "  Modbus directory : ${MODBUS_DIR}")
    message(STATUS "  Modbus binary    : ${MODBUS_BIN}")
    message(STATUS "  Modbus library   : ${MODBUS_STATIC_LIB}")
    message(STATUS "  Modbus includes  : ${MODBUS_INCLUDES}")
  else ()
    add_subdirectory(extern/libmodbus)
    list(APPEND gos_pid_toolkit_lib_modbus_include
      "${CMAKE_CURRENT_BINARY_DIR}/extern/libmodbus/src")
  endif ()
endif ()
list(APPEND gos_pid_toolkit_lib_modbus_include
  "${gos_pid_toolkit_lib_modbus_path}/src"
  ${gos_pid_toolkit_lib_modbus_path})

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
  list(APPEND gos_pid_toolkit_cpp_public_header
    "${gos_pid_toolkit_cpp_version_include_file}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/exception.h")
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/pid/version.h.in"
    "include/cpp/gos/pid/toolkit/pid/version.h"
    @ONLY)
  set(gos_pid_toolkit_pid_cpp_version_include_file
    "${CMAKE_CURRENT_BINARY_DIR}/include/cpp/gos/pid/toolkit/pid/version.h")
  list(APPEND gos_pid_toolkit_pid_cpp_public_header
    "${gos_pid_toolkit_pid_cpp_version_include_file}"
#    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/pid/exception.h"
    )
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/tune/version.h.in"
    "include/cpp/gos/pid/toolkit/tune/version.h"
    @ONLY)
  set(gos_pid_toolkit_tune_cpp_version_include_file
    "${CMAKE_CURRENT_BINARY_DIR}/include/cpp/gos/pid/toolkit/tune/version.h")
  list(APPEND gos_pid_toolkit_tune_cpp_public_header
    "${gos_pid_toolkit_tune_cpp_version_include_file}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/tune/type.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/tune/settings.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/tune/internals.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/toolkit/tune/parameters.h")
  list(APPEND gos_pid_arduino_modbus_master_cpp_library_public_header
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/modbus/master.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/modbus/types.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/arduino/modbus/retry.h")
  list(APPEND gos_pid_tuning_black_box_library_public_header
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/tuning/blackbox.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/tuning/types.h")
  set(gos_pid_toolkit_cpp_binary_include_dir
    "${CMAKE_CURRENT_BINARY_DIR}/include/cpp")
  list(APPEND gos_pid_toolkit_cpp_include
    "${gos_pid_toolkit_cpp_include_dir}"
    "${gos_pid_toolkit_cpp_binary_include_dir}")
  set(gos_pid_toolkit_tune_cpp_library_dir 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/libpidtoolkitui")
  set(gos_pid_toolkit_cpp_library_target libpidtoolkitcpp)
  set(gos_pid_toolkit_pid_cpp_library_target libpidtoolkitpid)
  set(gos_pid_toolkit_tune_cpp_library_target libpidtoolkittune)
  set(gos_pid_arduino_modbus_master_library_target libpidarduinomodbusmaster)
  set(gos_pid_tuning_black_box_library_target libpidtuningblackbox)
  set(gos_pid_toolkit_ui_cpp_plugin_target pidtoolkitplugin)
  set(gos_pid_black_box_tuning_target pidblackboxtuning)
  set(gos_pid_toolkit_ui_target pidtoolkitui)
  set(gos_build_dependency_boost ON)

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

  if (GOS_PID_TOOLKIT_UI)
    find_package(Qt5 COMPONENTS REQUIRED
      QuickControls2
      SerialPort
      Network
      Widgets
      Charts
      OpenGL
      Quick
      Core
      Qml
      Gui)
    get_target_property(gos_pid_toolkit_qt_quick_controls_2_runtime
      Qt5::QuickControls2 "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_serial_port_runtime
      Qt5::SerialPort "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_network_runtime
      Qt5::Network "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_widgets_runtime
      Qt5::Widgets "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_charts_runtime
      Qt5::Charts "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_open_gl_runtime
      Qt5::OpenGL "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_quick_runtime
      Qt5::Quick "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_core_runtime
      Qt5::Core "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_qml_runtime
      Qt5::Qml "IMPORTED_LOCATION_RELEASE")
    get_target_property(gos_pid_toolkit_qt_gui_runtime
      Qt5::Gui "IMPORTED_LOCATION_RELEASE")

    list(APPEND gos_pid_toolkit_ui_cpp_qt_libraries
      Qt5::QuickControls2
      Qt5::Widgets
      Qt5::Charts
      Qt5::OpenGL
      Qt5::Quick
      Qt5::Core
      Qt5::Qml
      Qt5::Gui)
    list(APPEND gos_pid_toolkit_ui_cpp_qt_ui_libraries
      ${gos_pid_toolkit_ui_cpp_qt_libraries}
      Qt5::SerialPort)

    list(APPEND gos_pid_toolkit_ui_cpp_qt_include
      ${Qt5QuickControls2_INCLUDE_DIRS}
      ${Qt5Widgets_INCLUDE_DIRS}
      ${Qt5Charts_INCLUDE_DIRS}
      ${Qt5OpenGL_INCLUDE_DIRS}
      ${Qt5Quick_INCLUDE_DIRS}
      ${Qt5Core_INCLUDE_DIRS}
      ${Qt5Qml_INCLUDE_DIRS}
      ${Qt5Gui_INCLUDE_DIRS})
    list(APPEND gos_pid_toolkit_ui_cpp_qt_ui_include
      ${gos_pid_toolkit_ui_cpp_qt_include}
      ${Qt5SerialPort_INCLUDE_DIRS})

    list(APPEND gos_pid_toolkit_ui_cpp_qt_definitions
      ${Qt5QuickControls2_DEFINITIONS}
      ${Qt5Widgets_DEFINITIONS}
      ${Qt5Charts_DEFINITIONS}
      ${Qt5OpenGL_DEFINITIONS}
      ${Qt5Quick_DEFINITIONS}
      ${Qt5Core_DEFINITIONS}
      ${Qt5Qml_DEFINITIONS}
      ${Qt5Gui_DEFINITIONS})
    list(APPEND gos_pid_toolkit_ui_cpp_ui_definitions
      ${gos_pid_toolkit_ui_cpp_qt_definitions}
      ${Qt5SerialPort_DEFINITIONS})

    list(APPEND gos_pid_toolkit_ui_cpp_qt_compile_definitions
      ${Qt5QuickControls2_COMPILE_DEFINITIONS}
      ${Qt5Widgets_COMPILE_DEFINITIONS}
      ${Qt5Charts_COMPILE_DEFINITIONS}
      ${Qt5OpenGL_COMPILE_DEFINITIONS}
      ${Qt5Quick_COMPILE_DEFINITIONS}
      ${Qt5Core_COMPILE_DEFINITIONS}
      ${Qt5Qml_COMPILE_DEFINITIONS}
      ${Qt5Gui_COMPILE_DEFINITIONS})
    list(APPEND gos_pid_toolkit_ui_cpp_qt_compile_ui_definitions
      ${gos_pid_toolkit_ui_cpp_qt_compile_definitions}
      ${Qt5SerialPort_COMPILE_DEFINITIONS})

    # Empty so not needed
    list(APPEND gos_pid_toolkit_ui_cpp_qt_compile_flags
      ${Qt5QuickControls2_EXECUTABLE_COMPILE_FLAGS}
      ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}
      ${Qt5Charts_EXECUTABLE_COMPILE_FLAGS}
      ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}
      ${Qt5Quick_EXECUTABLE_COMPILE_FLAGS}
      ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}
      ${Qt5Qml_EXECUTABLE_COMPILE_FLAGS}
      ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS})
    list(APPEND gos_pid_toolkit_ui_cpp_qt_ui_compile_flags
      ${gos_pid_toolkit_ui_cpp_qt_compile_flags}
      ${Qt5SerialPort_EXECUTABLE_COMPILE_FLAGS})

    set(gos_pid_toolkit_ui_cpp_plugin_source_dir
      "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/pidtoolkitplugin/Pid/Toolkit")
    set(gos_pid_toolkit_ui_cpp_plugin_include_dir
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/plugin")
    list(APPEND gos_pid_toolkit_ui_cpp_plugin_base_source
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/plugin/pathvalidator.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/plugin/plugin.h")
    set(gos_pid_toolkit_ui_cpp_plugin_qmldir_file
      "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/pidtoolkitplugin/Pid/Toolkit/qmldir")

    list(APPEND gos_pid_toolkit_ui_model_cpp_library_source
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/restriction.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/operation.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/accuracy.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/triplet.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/serial.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/number.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/modbus.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/format.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/status.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/factor.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/tuning.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/force.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/range.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/ptu.h")
    list(APPEND gos_pid_toolkit_ui_model_cpp_library_public_header
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/restriction.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/operation.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/enumerate.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/accuracy.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/interval.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/triplet.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/serial.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/number.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/modbus.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/format.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/status.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/status.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/factor.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/tuning.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/force.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/range.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/types.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/mode.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/model/ptu.h")
    set(gos_pid_toolkit_ui_model_cpp_library_target libpidtoolkituimodel)

    list(APPEND gos_pid_toolkit_ui_view_model_cpp_library_source
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/view/model/blackbox.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/view/model/modbus.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/view/model/tuning.h")
    list(APPEND gos_pid_toolkit_ui_view_model_cpp_library_public_header
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/view/model/blackbox.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/view/model/modbus.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/view/model/tuning.h")
    set(gos_pid_toolkit_ui_view_model_cpp_library_target libpidtoolkituiviewmodel)

    list(APPEND gos_pid_toolkit_ui_configuration_cpp_library_source
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/controller.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/blackbox.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/modbus.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/tuning.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/timer.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/ui.h")
    list(APPEND gos_pid_toolkit_ui_configuration_cpp_library_public_header
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/interface.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/controller.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/blackbox.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/modbus.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/tuning.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/timer.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/configuration/ui.h")
    set(gos_pid_toolkit_ui_configuration_cpp_library_target
      libpidtoolkituiconfiguration)

    #list(APPEND gos_pid_toolkit_ui_cpp_library_source )
    list(APPEND gos_pid_toolkit_ui_cpp_library_public_header
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/formatting.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp/gos/pid/ui/types.h")
    set(gos_pid_toolkit_ui_cpp_library_target libpidtoolkitui)

  endif (GOS_PID_TOOLKIT_UI)

endif (GOS_PID_TOOLKIT_CPP)

if (BUILD_DOCS)
  list(APPEND gos_pid_toolkit_doxygen_source
    ${gos_pid_toolkit_cpp_include_dir}
    ${gos_pid_toolkit_cpp_source_dir})
  set(gos_pid_toolkit_doxygen_output_directory ${CMAKE_BINARY_DIR}/doc)
  set(gos_pid_toolkit_doxygen_working_directory ${PROJECT_SOURCE_DIR})
  set(gos_pid_toolkit_doxygen_main_page_mdfile "${PROJECT_SOURCE_DIR}/README.md")
  set(gos_pid_toolkit_doxygen_main_target doxygetpidtoolkit)
  add_subdirectory(doc)
endif (BUILD_DOCS)

if (GOS_PID_TOOLKIT_C)
  add_subdirectory(src/c)
endif (GOS_PID_TOOLKIT_C)

if (gos_build_dependency_boost)
  set(Boost_USE_MULTITHREADED        ON)
  set(Boost_USE_STATIC_RUNTIME      OFF)
  if (BUILD_SHARED_LIBS)
    set(Boost_USE_STATIC_LIBS       OFF)    
  else ()
    set(Boost_USE_STATIC_LIBS        ON)
  endif ()

  list(APPEND gos_pid_toolkit_boost_package
    regex
    system
    date_time
    filesystem
    serialization
    program_options)
 list(REMOVE_DUPLICATES gos_pid_toolkit_boost_package)

  if (gos_pid_toolkit_boost_package)
    find_package(Boost 1.62 COMPONENTS REQUIRED
      ${gos_pid_toolkit_boost_package})
  else ()
    find_package(Boost 1.62)
  endif ()

# if (GOS_PID_TOOLKIT_CPP)
#   list(APPEND gos_pid_toolkit_cpp_include
#     ${Boost_INCLUDE_DIRS})
# endif (GOS_PID_TOOLKIT_CPP)
endif ()

if (GOS_PID_TOOLKIT_CPP)
  add_subdirectory(src/cpp)
endif ()

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
message(STATUS "  CMAKE_SYSTEM_NAME       : ${CMAKE_SYSTEM_NAME}")
message(STATUS "  CMAKE_GENERATOR         : ${CMAKE_GENERATOR}")
message(STATUS "  CMAKE_MODULE_PATH       : ${CMAKE_MODULE_PATH}")
if (GOS_PID_TOOLKIT_C)
message(STATUS "  C Compiler ID           : ${CMAKE_C_COMPILER_ID}")
endif ()
if (GOS_PID_TOOLKIT_CPP)
message(STATUS "  C++ Compiler ID         : ${CMAKE_CXX_COMPILER_ID}")
if (GOS_PID_TOOLKIT_UI)
message(STATUS "  Qt Definitions          : ${gos_pid_toolkit_ui_cpp_qt_definitions}")
message(STATUS "  Qt Compile Definitions  : ${gos_pid_toolkit_ui_cpp_qt_compile_definitions}")
endif ()
endif ()
message(STATUS "  Build type              : ${CMAKE_BUILD_TYPE}")
if (gos_build_dependency_boost)
message(STATUS "  Boost version           : ${Boost_VERSION}")
message(STATUS "  Boost include dir       : ${Boost_INCLUDE_DIRS}")
endif ()
if (GOS_PID_TOOLKIT_TEST)
message(STATUS "  Google Test dir         : ${GOS_PID_TOOLKIT_GOOGLE_TEST_PATH}")
message(STATUS "  Force Shared CRT        : ${gtest_force_shared_crt}")
message(STATUS "  Build and execute unit tests")
endif ()
message(STATUS "")
