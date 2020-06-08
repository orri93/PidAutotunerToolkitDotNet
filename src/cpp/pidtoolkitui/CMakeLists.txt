option(GOS_PID_TOOLKIT_UI_FETCH_PLUGIN
  "Get the PID toolkit plugin to be able to run from build" ON)

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
  ${extern_libmodbus_include}
  ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND gos_pid_toolkit_ui_definitions
  GOS_PID_TUNING_UI_LIB_SHARED)

list(APPEND gos_pid_toolkit_ui_libraries
  ${gos_pid_toolkit_ui_configuration_cpp_library_target}
  ${gos_pid_toolkit_ui_view_model_cpp_library_target}
  ${gos_pid_arduino_modbus_master_library_target}
  ${gos_pid_toolkit_ui_model_cpp_library_target}
  ${gos_pid_tuning_black_box_library_target}
  ${gos_pid_toolkit_ui_cpp_library_target}
  ${gos_pid_toolkit_ui_cpp_plugin_target}
  ${gos_pid_toolkit_cpp_library_target}
  ${gos_pid_toolkit_lib_modbus_lib}
  Boost::program_options
  Boost::filesystem
  Boost::date_time
# Boost::log_setup
  Boost::regex
  Qt5::QuickControls2
  Qt5::SerialPort
  Qt5::Widgets
  Qt5::Charts
  Qt5::OpenGL
  Qt5::Quick  
  Qt5::Core
  Qt5::Qml
  ws2_32)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

find_package(Qt5 COMPONENTS REQUIRED
  QuickControls2
  SerialPort
  Charts
  Quick
  Core
  Qml)

qt5_add_resources(gos_pid_toolkit_ui_resources
  ${CMAKE_CURRENT_SOURCE_DIR}/pidtoolkit.qrc)

list(APPEND gos_pid_toolkit_ui_source
  ${gos_pid_toolkit_ui_resources})

add_executable(${gos_pid_toolkit_ui_target}
  ${gos_pid_toolkit_ui_source})

target_include_directories(${gos_pid_toolkit_ui_target} PRIVATE
  ${gos_pid_toolkit_ui_include})

target_compile_features(${gos_pid_toolkit_ui_target} PRIVATE
  cxx_auto_type
  cxx_generic_lambdas)

target_link_libraries(${gos_pid_toolkit_ui_target} PRIVATE
  ${gos_pid_toolkit_ui_libraries})

target_compile_definitions(${gos_pid_toolkit_ui_target} PRIVATE
  ${gos_pid_toolkit_ui_definitions})

if(GOS_PID_TOOLKIT_UI_FETCH_PLUGIN)
  set(gos_pid_toolkit_ui_cpp_plugin_destination_folder
    "${CMAKE_CURRENT_BINARY_DIR}/Pid/Toolkit")
  set(gos_pid_toolkit_ui_cpp_plugin_destination_qmldir
    "${gos_pid_toolkit_ui_cpp_plugin_destination_folder}/qmldir")
  set(gos_pid_toolkit_ui_cpp_plugin_source_runtime
    "$<TARGET_FILE:${gos_pid_toolkit_ui_cpp_plugin_target}>")
  set(gos_pid_toolkit_ui_cpp_plugin_binary_runtime
    "${gos_pid_toolkit_ui_cpp_plugin_destination_folder}/$<TARGET_FILE_NAME:${gos_pid_toolkit_ui_cpp_plugin_target}>")

  configure_file(${gos_pid_toolkit_ui_cpp_plugin_qmldir_file}
    ${gos_pid_toolkit_ui_cpp_plugin_destination_qmldir} COPYONLY)

  set(COPY_RUNTIME_COMMAND ${CMAKE_COMMAND} -E copy "\"${gos_pid_toolkit_ui_cpp_plugin_source_runtime}\"" "\"${gos_pid_toolkit_ui_cpp_plugin_binary_runtime}\"")
  add_custom_command(TARGET ${gos_pid_toolkit_ui_target}
    POST_BUILD
    DEPENDS ${gos_pid_toolkit_ui_cpp_plugin_source_runtime}
    COMMAND ${COPY_RUNTIME_COMMAND}
    COMMENT "Fetch the plugin for the PID Toolkit UI")
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

install(TARGETS ${gos_pid_toolkit_ui_target} DESTINATION bin/ui)
if (GOS_PID_TOOLKIT_INSTALL_CONFIGURATION)
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/configuration.ini DESTINATION bin/ui)
endif ()