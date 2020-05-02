set(gos_pid_toolkit_ui_target pidtoolkitui)

list(APPEND gos_pid_toolkit_ui_source
  "model/mode.cpp"
  "model/tuning.cpp"
  "model/interval.cpp"
  "orchestration.cpp"
  "configuration.cpp"
  "pidtoolkitui.cpp"
  "orchestration.h"
  "configuration.h"
  "resources.qrc"
  "items.cpp"
  "items.h")

list(APPEND gos_pid_toolkit_ui_include
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${extern_libmodbus_include})

list(APPEND gos_pid_toolkit_ui_libraries
  ${gos_pid_arduino_modbus_master_library_target}
  ${gos_pid_tuning_black_box_library_target}
  ${gos_pid_toolkit_ui_cpp_library_target}
  ${gos_pid_toolkit_cpp_library_target}
  ${gos_pid_toolkit_lib_modbus_lib}
  Qt5::QuickControls2
  Qt5::Charts
  Qt5::Quick  
  Qt5::Core
  Qt5::Qml
  ws2_32)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

find_package(Qt5 COMPONENTS REQUIRED
  QuickControls2
  Charts
  Quick
  Core
  Qml)

add_executable(${gos_pid_toolkit_ui_target}
  ${gos_pid_toolkit_ui_source})

target_include_directories(${gos_pid_toolkit_ui_target} PRIVATE
  ${gos_pid_toolkit_ui_include})

target_link_libraries(${gos_pid_toolkit_ui_target}
  ${gos_pid_toolkit_ui_libraries})

add_custom_command(TARGET ${gos_pid_toolkit_ui_target} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/configuration.ini
    $<TARGET_FILE_DIR:${gos_pid_toolkit_ui_target}>)

install(TARGETS ${gos_pid_toolkit_ui_target}
  LIBRARY DESTINATION bin/ui
  ARCHIVE DESTINATION bin/ui)
