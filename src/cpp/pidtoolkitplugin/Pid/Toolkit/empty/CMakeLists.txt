set(gos_pid_toolkit_ui_cpp_dummy_target pidtoolkitempty)

set(GOS_PID_TOOLKIT_PLUGIN ${gos_pid_toolkit_ui_cpp_dummy_target})
set(GOS_PID_TOOLKIT_PLUGIN_QMLDIR_TOOLKIT_ITEM
  "singleton Toolkit 1.0 qrc:///pidtoolkit/Toolkit.qml")
set(gos_pid_toolkit_ui_cpp_dummy_qmldir_file
  "${CMAKE_CURRENT_BINARY_DIR}/qmldir")
configure_file(${gos_pid_toolkit_ui_cpp_plugin_qmldir_in}
  ${gos_pid_toolkit_ui_cpp_dummy_qmldir_file} @ONLY)

set(GOS_PID_TOOLKIT_PLUGIN_QRC_PREFIX_ROOT
  "<file alias=\"qtquickcontrols2.conf\">empty/qtquickcontrols2.conf</file>")
set(GOS_PID_TOOLKIT_PLUGIN_QRC_TOOLKIT_ITEM
  "<file alias=\"Toolkit.qml\">empty/Toolkit.qml</file>")
set(GOS_PID_TOOLKIT_PLUGIN_QRC_PATH "empty")
configure_file(${gos_pid_toolkit_ui_cpp_plugin_qrc_in}
  ${gos_pid_toolkit_ui_cpp_dummy_qrc} @ONLY)

list(APPEND gos_pid_toolkit_ui_cpp_dummy_source
# ${gos_pid_toolkit_ui_cpp_dummy_qrc}
  ${gos_pid_toolkit_ui_cpp_dummy_qmldir_file}
  ${gos_pid_toolkit_ui_cpp_plugin_base_source})

qt5_add_resources(gos_pid_toolkit_ui_cpp_dummy_resources
  ${gos_pid_toolkit_ui_cpp_dummy_qrc})

list(APPEND gos_pid_toolkit_ui_cpp_dummy_source
# ${gos_pid_toolkit_ui_cpp_dummy_qrc}
  ${gos_pid_toolkit_ui_cpp_dummy_resources})

list(APPEND gos_pid_toolkit_ui_cpp_dummy_include
  ${gos_pid_toolkit_ui_cpp_qt_include}
  ${gos_pid_toolkit_cpp_include}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS})

list(APPEND gos_pid_toolkit_ui_cpp_dummy_libraries
  ${gos_pid_toolkit_ui_cpp_qt_libraries})

list(APPEND gos_pid_toolkit_ui_cpp_dummy_definitions
  ${gos_pid_toolkit_ui_cpp_qt_compile_definitions})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(${gos_pid_toolkit_ui_cpp_dummy_target} SHARED
  ${gos_pid_toolkit_ui_cpp_dummy_source})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_toolkit_ui_cpp_dummy_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(${gos_pid_toolkit_ui_cpp_dummy_target} PUBLIC
  ${gos_pid_toolkit_ui_cpp_dummy_include})

if (gos_pid_toolkit_ui_cpp_dummy_definitions)
  target_compile_definitions(${gos_pid_toolkit_ui_cpp_dummy_target} PRIVATE
    ${gos_pid_toolkit_ui_cpp_dummy_definitions})
endif ()

target_compile_features(${gos_pid_toolkit_ui_cpp_dummy_target} PRIVATE
  cxx_auto_type
  cxx_generic_lambdas)

target_link_libraries(${gos_pid_toolkit_ui_cpp_dummy_target} PRIVATE
  ${gos_pid_toolkit_ui_cpp_dummy_libraries})

set(gos_pid_toolkit_ui_cpp_dummy_destination 
  "plugin/empty/Pid/Toolkit")

list(APPEND gos_pid_toolkit_ui_cpp_dummy_extra_files
  ${gos_pid_toolkit_ui_cpp_dummy_qmldir_file})

if(GOS_DEPLOY_PDB_FILES)
  install(FILES "$<TARGET_PDB_FILE:${gos_pid_toolkit_ui_cpp_dummy_target}>"
    DESTINATION pdb/empty
    COMPONENT pdb/empty)
endif()

install(TARGETS ${gos_pid_toolkit_ui_cpp_dummy_target}
  RUNTIME DESTINATION ${gos_pid_toolkit_ui_cpp_dummy_destination}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
install(FILES ${gos_pid_toolkit_ui_cpp_dummy_extra_files}
  DESTINATION ${gos_pid_toolkit_ui_cpp_dummy_destination})
