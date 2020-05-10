list(APPEND gos_pid_toolkit_ui_cpp_plugin_source
  "floatvalidator.cpp"
  "pathvalidator.cpp"
  "connection.cpp"
  "plugin.cpp")

find_package(Qt5 COMPONENTS REQUIRED
  QuickControls2
  Quick
  Core
  Qml)

qt5_add_resources(gos_pid_toolkit_ui_cpp_plugin_resources
  ${CMAKE_CURRENT_LIST_DIR}/qml/pidtoolkitui.qrc)

list(APPEND gos_pid_toolkit_ui_cpp_plugin_source
  ${gos_pid_toolkit_ui_cpp_plugin_resources})

list(APPEND gos_pid_toolkit_ui_cpp_plugin_include
  ${gos_pid_toolkit_cpp_include}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Qt5Core_INCLUDE_DIRS}
  ${QtQml_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS})

#list(APPEND gos_pid_toolkit_ui_cpp_plugin_definitions
#  GOS_PID_TUNING_UI_LIB_LIBRARY
#  GOS_PID_TUNING_UI_LIB_SHARED)

list(APPEND gos_pid_toolkit_ui_cpp_plugin_libraries
  Qt5::QuickControls2
  Qt5::Quick  
  Qt5::Core
  Qt5::Qml)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

add_library(${gos_pid_toolkit_ui_cpp_plugin_target} SHARED
  ${gos_pid_toolkit_ui_cpp_plugin_source})

#list(APPEND gos_pid_toolkit_ui_cpp_plugin_include ${Boost_INCLUDE_DIRS})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_toolkit_ui_cpp_plugin_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(${gos_pid_toolkit_ui_cpp_plugin_target} PUBLIC
  ${gos_pid_toolkit_ui_cpp_plugin_include})

#target_compile_definitions(${gos_pid_toolkit_ui_cpp_plugin_target} PRIVATE
#  ${gos_pid_toolkit_ui_cpp_plugin_definitions})
target_compile_features(${gos_pid_toolkit_ui_cpp_plugin_target} PRIVATE
  cxx_auto_type
  cxx_generic_lambdas)

target_link_libraries(${gos_pid_toolkit_ui_cpp_plugin_target} PRIVATE
  ${gos_pid_toolkit_ui_cpp_plugin_libraries})

if (gos_pid_toolkit_ui_cpp_plugin_public_header)
  set_target_properties(${gos_pid_toolkit_ui_cpp_plugin_target}
    PROPERTIES PUBLIC_HEADER
    "${gos_pid_toolkit_ui_cpp_plugin_public_header}")
endif ()

install(TARGETS ${gos_pid_toolkit_ui_cpp_plugin_target}
  RUNTIME DESTINATION bin/ui/Pid/Toolkit
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/cpp/gos/pid/toolkit/ui
  ARCHIVE DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/qmldir
  DESTINATION bin/ui/Pid/Toolkit)