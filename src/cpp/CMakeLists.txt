if (GOS_PID_ARDUINO_BASED_TUNING)
  add_subdirectory(libarduinobasedautotuning)
endif (GOS_PID_ARDUINO_BASED_TUNING)

if (GOS_PID_TOOLKIT_CPP)
  add_subdirectory(libpidarduinomodbusmaster)
  add_subdirectory(libpidtuningblackbox)
  add_subdirectory(libpidtoolkit)
  add_subdirectory(libpidtoolkittune)
  add_subdirectory(libpidtoolkitpid)
  add_subdirectory(pidblackboxtuning)
  
  if (GOS_PID_TOOLKIT_UI)
    set(gos_pid_toolkit_ui_cpp_plugin_qmldir_in
      "${CMAKE_CURRENT_SOURCE_DIR}/pidtoolkitplugin/Pid/Toolkit/qmldir.in")

    add_subdirectory(libpidtoolkituiconfiguration)
    add_subdirectory(libpidtoolkituiviewmodel)
    add_subdirectory(libpidtoolkituimodel)
    add_subdirectory(libpidtoolkitui)
    add_subdirectory(pidtoolkitplugin)
    add_subdirectory(pidtoolkitui)
  endif ()

  if (GOS_PID_TOOLKIT_SERVICE)
    add_subdirectory(libpidtoolkitservice)
    add_subdirectory(pidtoolkitserver)
  endif ()

endif (GOS_PID_TOOLKIT_CPP)
