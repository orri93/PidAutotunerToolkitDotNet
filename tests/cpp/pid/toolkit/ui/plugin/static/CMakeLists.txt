list(APPEND gos_pid_toolkit_ui_plugin_static_for_test_source
  "${gos_pid_toolkit_ui_cpp_plugin_include_dir}/pathvalidator.h"
  "${gos_pid_toolkit_ui_cpp_plugin_source_dir}/floatvalidator.cpp"
  "${gos_pid_toolkit_ui_cpp_plugin_source_dir}/pathvalidator.cpp")

find_package(Qt5 COMPONENTS REQUIRED
  QuickControls2
  Quick
  Core
  Gui
  Qml)

list(APPEND gos_pid_toolkit_ui_plugin_static_for_test_include
  ${gos_pid_toolkit_ui_cpp_plugin_source_dir}
  ${gos_pid_toolkit_cpp_include}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Qml_INCLUDE_DIRS})

message(STATUS "Qt5 Core Include Directories: ${Qt5Core_INCLUDE_DIRS}")
message(STATUS "Qt5 GUI Include Directories: ${Qt5Gui_INCLUDE_DIRS}")
message(STATUS "Qt5 QML Include Directories: ${Qt5Qml_INCLUDE_DIRS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

add_library(${gos_pid_toolkit_ui_plugin_static_for_test_target}
  ${gos_pid_toolkit_ui_plugin_static_for_test_source})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_toolkit_ui_plugin_static_for_test_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(${gos_pid_toolkit_ui_plugin_static_for_test_target} PUBLIC
  ${gos_pid_toolkit_ui_plugin_static_for_test_include})

if (gos_pid_toolkit_ui_plugin_static_for_test_definitions)
  target_compile_definitions(${gos_pid_toolkit_ui_plugin_static_for_test_target} PRIVATE
    ${gos_pid_toolkit_ui_plugin_static_for_test_definitions})
endif ()

target_compile_features(${gos_pid_toolkit_ui_plugin_static_for_test_target} PRIVATE
  cxx_auto_type
  cxx_generic_lambdas)

if (gos_pid_toolkit_ui_plugin_static_for_test_public_header)
  set_target_properties(${gos_pid_toolkit_ui_plugin_static_for_test_target}
    PROPERTIES PUBLIC_HEADER
    "${gos_pid_toolkit_ui_plugin_static_for_test_public_header}")
endif ()
