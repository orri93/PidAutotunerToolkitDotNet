option(GOS_PID_TOOLKIT_UI_FETCH_PLUGIN
  "Get the PID toolkit plugin to be able to run from build" ON)

set(GOS_PID_TOOLKIT_PLUGIN ${gos_pid_toolkit_ui_cpp_plugin_target})
set(gos_pid_toolkit_ui_cpp_plugin_qmldir_binary_file
  "${CMAKE_CURRENT_BINARY_DIR}/qmldir")
configure_file(${gos_pid_toolkit_ui_cpp_plugin_qmldir_in}
  ${gos_pid_toolkit_ui_cpp_plugin_qmldir_binary_file} @ONLY)

list(APPEND gos_pid_toolkit_ui_source
  "orchestration.cpp"
  "configuration.cpp"
  "pidtoolkitui.cpp"
  "orchestration.h"
  "configuration.h"
  "models.cpp"
  "models.h")

list(APPEND gos_pid_toolkit_ui_include
  ${gos_pid_toolkit_tune_cpp_library_dir}
  ${gos_pid_toolkit_ui_cpp_qt_ui_include}
  ${extern_libmodbus_include}
  ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND gos_pid_toolkit_ui_definitions
  ${gos_pid_toolkit_ui_cpp_qt_compile_definitions}
  GOS_PID_TUNING_UI_LIB_SHARED)

list(APPEND gos_pid_toolkit_ui_libraries
  ${gos_pid_toolkit_ui_configuration_cpp_library_target}
  ${gos_pid_toolkit_ui_view_model_cpp_library_target}
  ${gos_pid_arduino_modbus_master_library_target}
  ${gos_pid_toolkit_ui_model_cpp_library_target}
  ${gos_pid_tuning_black_box_library_target}
  ${gos_pid_toolkit_ui_cpp_qt_ui_libraries}
  ${gos_pid_toolkit_ui_cpp_library_target}
  ${gos_pid_toolkit_ui_cpp_plugin_target}
  ${gos_pid_toolkit_cpp_library_target}
  ${gos_pid_toolkit_lib_modbus_lib}
  Boost::program_options
  Boost::filesystem
  Boost::date_time
# Boost::log_setup
  Boost::regex)

if (WIN32)
  list(APPEND gos_pid_toolkit_ui_libraries ws2_32)
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

qt5_add_resources(gos_pid_toolkit_ui_resources
  ${CMAKE_CURRENT_SOURCE_DIR}/pidtoolkit.qrc)

list(APPEND gos_pid_toolkit_ui_source
  ${gos_pid_toolkit_ui_resources})

add_executable(${gos_pid_toolkit_ui_target}
  ${gos_pid_toolkit_ui_source})

set(gos_pid_toolkit_ui_cpp_plugin_destination_folder
  "$<TARGET_FILE_DIR:${gos_pid_toolkit_ui_target}>/Pid/Toolkit")

target_include_directories(${gos_pid_toolkit_ui_target} PRIVATE
  ${gos_pid_toolkit_ui_include})

target_compile_features(${gos_pid_toolkit_ui_target} PRIVATE
  cxx_auto_type
  cxx_generic_lambdas)

target_link_libraries(${gos_pid_toolkit_ui_target} PRIVATE
  ${gos_pid_toolkit_ui_libraries})

target_compile_definitions(${gos_pid_toolkit_ui_target} PRIVATE
  ${gos_pid_toolkit_ui_definitions})

set(gos_pid_toolkit_ui_destination 
  "bin/ui")
set(gos_pid_toolkit_ui_cpp_plugin_destination 
  "${gos_pid_toolkit_ui_destination}/Pid/Toolkit")

list(APPEND gos_pid_toolkit_ui_cpp_other_install_files 
  "${CMAKE_CURRENT_SOURCE_DIR}/configuration.ini")

if(GOS_PID_TOOLKIT_UI_FETCH_PLUGIN)
  set(gos_pid_toolkit_ui_cpp_plugin_source_runtime
    "$<TARGET_FILE:${gos_pid_toolkit_ui_cpp_plugin_target}>")
  set(gos_pid_toolkit_ui_cpp_plugin_binary_runtime
    "${gos_pid_toolkit_ui_cpp_plugin_destination_folder}/$<TARGET_FILE_NAME:${gos_pid_toolkit_ui_cpp_plugin_target}>")

  set(COPY_RUNTIME_COMMAND ${CMAKE_COMMAND} -E copy "\"${gos_pid_toolkit_ui_cpp_plugin_source_runtime}\"" "\"${gos_pid_toolkit_ui_cpp_plugin_binary_runtime}\"")
  add_custom_command(TARGET ${gos_pid_toolkit_ui_target}
    POST_BUILD
    DEPENDS ${gos_pid_toolkit_ui_cpp_plugin_source_runtime}
    COMMAND ${COPY_RUNTIME_COMMAND}
    COMMENT "Fetch the plugin for the PID Toolkit UI")

  set(gos_pid_toolkit_ui_cpp_plugin_qmldir_file
    "${gos_pid_toolkit_ui_cpp_plugin_destination_folder}/qmldir")
  set(COPY_QMLDIR_COMMAND ${CMAKE_COMMAND} -E copy "\"${gos_pid_toolkit_ui_cpp_plugin_qmldir_binary_file}\"" "\"${gos_pid_toolkit_ui_cpp_plugin_qmldir_file}\"")
  add_custom_command(TARGET ${gos_pid_toolkit_ui_target}
    POST_BUILD
    DEPENDS ${gos_pid_toolkit_ui_cpp_plugin_qmldir_binary_file}
    COMMAND ${COPY_QMLDIR_COMMAND}
    COMMENT "Copy the qmldir for the PID Toolkit UI")
endif()

if (GOS_PID_TOOLKIT_INSTALL_CONFIGURATION)
  add_custom_command(TARGET ${gos_pid_toolkit_ui_target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_CURRENT_SOURCE_DIR}/configuration.ini
      $<TARGET_FILE_DIR:${gos_pid_toolkit_ui_target}>)
endif ()
if(GOS_DEPLOY_PDB_FILES)
  install(FILES "$<TARGET_PDB_FILE:${gos_pid_toolkit_ui_target}>"
    DESTINATION pdb
    COMPONENT pdb)
endif()

if(GOS_PID_TOOLKIT_INSTALL_DEPENDENCIES)
  list(APPEND gos_pid_toolkit_ui_runtimes
    ${gos_pid_toolkit_qt_quick_controls_2_runtime}
    ${gos_pid_toolkit_qt_serial_port_runtime}
    ${gos_pid_toolkit_qt_network_runtime}
    ${gos_pid_toolkit_qt_widgets_runtime}
    ${gos_pid_toolkit_qt_charts_runtime}
    ${gos_pid_toolkit_qt_open_gl_runtime}
    ${gos_pid_toolkit_qt_quick_runtime}
    ${gos_pid_toolkit_qt_core_runtime}
    ${gos_pid_toolkit_qt_qml_runtime}
    ${gos_pid_toolkit_qt_gui_runtime})
  install(FILES ${gos_pid_toolkit_ui_runtimes}
    DESTINATION ${gos_pid_toolkit_ui_destination})
endif()

install(TARGETS ${gos_pid_toolkit_ui_target}
  DESTINATION ${gos_pid_toolkit_ui_destination})
if (GOS_PID_TOOLKIT_INSTALL_CONFIGURATION)
  install(FILES ${gos_pid_toolkit_ui_cpp_other_install_files}
  DESTINATION ${gos_pid_toolkit_ui_destination})
endif ()

# Install files into the Plugin folder
install(FILES ${gos_pid_toolkit_ui_cpp_plugin_qmldir_binary_file}
  DESTINATION ${gos_pid_toolkit_ui_cpp_plugin_destination})
