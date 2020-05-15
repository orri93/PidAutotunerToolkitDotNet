set(gos_pid_toolkit_ui_plugin_test_target gospidtoolkituiplugin)

set(gos_pid_toolkit_ui_plugin_static_for_test_target gospidtoolkituistaticplugin)

add_subdirectory(static)

list(APPEND gos_pid_toolkit_ui_plugin_test_source
  pathvalidator.cpp)

find_package(Qt5 COMPONENTS REQUIRED
  QuickControls2
  Quick
  Core
  Gui
  Qml)

list(APPEND gos_pid_toolkit_ui_plugin_test_include
  ${gos_pid_toolkit_ui_cpp_plugin_source_dir}
  ${gos_pid_toolkit_cpp_include}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Qml_INCLUDE_DIRS})

list(APPEND gos_pid_toolkit_ui_plugin_test_libraries
  ${gos_pid_toolkit_ui_plugin_static_for_test_target}
  ${gos_pid_toolkit_gtest_libraries}
  Qt5::QuickControls2
  Qt5::Quick  
  Qt5::Core
  Qt5::Qml)

add_executable(${gos_pid_toolkit_ui_plugin_test_target}
  ${gos_pid_toolkit_ui_plugin_test_source})

target_include_directories(${gos_pid_toolkit_ui_plugin_test_target} PUBLIC
  ${gos_pid_toolkit_ui_plugin_test_include})

#target_compile_definitions(${gos_pid_toolkit_ui_plugin_test_target} PUBLIC
#  SOME_DEF)

target_link_libraries(${gos_pid_toolkit_ui_plugin_test_target}
  ${gos_pid_toolkit_ui_plugin_test_libraries})

#if(CLANG_TIDY_EXE)
#  set_target_properties(${gos_pid_toolkit_ui_plugin_test_target} PROPERTIES
#    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
#endif()

add_test(NAME gos_pid_toolkit_ui_plugin_test COMMAND
  ${gos_pid_toolkit_ui_plugin_test_target})
