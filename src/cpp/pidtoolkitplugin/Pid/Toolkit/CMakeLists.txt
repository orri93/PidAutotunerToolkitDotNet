option(GOS_PID_TOOLKIT_UI_PLUGIN_GENERATE_DUMMY
  "Generate dummy plugin for QML Types (only works with release builds)" OFF)

set(gos_pid_toolkit_ui_cpp_plugin_source_qmldir
  "${CMAKE_CURRENT_SOURCE_DIR}/qmldir")

list(APPEND gos_pid_toolkit_ui_cpp_plugin_base_source
  "${CMAKE_CURRENT_SOURCE_DIR}/pathvalidator.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/plugin.cpp")

list(APPEND gos_pid_toolkit_ui_cpp_plugin_source
  ${gos_pid_toolkit_ui_cpp_plugin_base_source}
# "${CMAKE_CURRENT_SOURCE_DIR}/pidtoolkitplugin.qrc"
  ${gos_pid_toolkit_ui_cpp_plugin_source_qmldir})

qt5_add_resources(gos_pid_toolkit_ui_cpp_plugin_resources
  "${CMAKE_CURRENT_SOURCE_DIR}/pidtoolkitplugin.qrc")

list(APPEND gos_pid_toolkit_ui_cpp_plugin_source
#  "${CMAKE_CURRENT_LIST_DIR}/pidtoolkitplugin.qrc")
 ${gos_pid_toolkit_ui_cpp_plugin_resources})

list(APPEND gos_pid_toolkit_ui_cpp_plugin_include
  ${gos_pid_toolkit_cpp_include}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Qml_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS})

list(APPEND gos_pid_toolkit_ui_cpp_plugin_libraries
  Qt5::QuickControls2
  Qt5::Widgets
  Qt5::Charts
  Qt5::OpenGL
  Qt5::Quick
  Qt5::Core
  Qt5::Qml)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(${gos_pid_toolkit_ui_cpp_plugin_target} SHARED
  ${gos_pid_toolkit_ui_cpp_plugin_source})

#list(APPEND gos_pid_toolkit_ui_cpp_plugin_include ${Boost_INCLUDE_DIRS})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_toolkit_ui_cpp_plugin_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(${gos_pid_toolkit_ui_cpp_plugin_target} PUBLIC
  ${gos_pid_toolkit_ui_cpp_plugin_include})

if (gos_pid_toolkit_ui_cpp_plugin_definitions)
  target_compile_definitions(${gos_pid_toolkit_ui_cpp_plugin_target} PRIVATE
    ${gos_pid_toolkit_ui_cpp_plugin_definitions})
endif ()

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

list(APPEND gos_pid_toolkit_ui_cpp_plugin_extra_files
  ${gos_pid_toolkit_ui_cpp_plugin_source_qmldir})

if(GOS_PID_TOOLKIT_UI_PLUGIN_GENERATE_DUMMY)
  set(gos_pid_toolkit_ui_cpp_dummy_qrc
    "${CMAKE_CURRENT_SOURCE_DIR}/empty.qrc")
  set(gos_pid_toolkit_ui_cpp_dummy_empty_qmldir
    "${CMAKE_CURRENT_SOURCE_DIR}/emptyqmldir")
  add_subdirectory(empty)
endif()

set(gos_pid_toolkit_ui_cpp_plugin_destination 
  "bin/ui/Pid/Toolkit")

if(GOS_DEPLOY_PDB_FILES)
  install(FILES "$<TARGET_PDB_FILE:${gos_pid_toolkit_ui_cpp_plugin_target}>"
    DESTINATION pdb
    COMPONENT pdb)
endif()

install(TARGETS ${gos_pid_toolkit_ui_cpp_plugin_target}
  RUNTIME DESTINATION ${gos_pid_toolkit_ui_cpp_plugin_destination}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/cpp/gos/pid/toolkit/ui
  ARCHIVE DESTINATION lib)
install(FILES ${gos_pid_toolkit_ui_cpp_plugin_extra_files}
  DESTINATION ${gos_pid_toolkit_ui_cpp_plugin_destination})
