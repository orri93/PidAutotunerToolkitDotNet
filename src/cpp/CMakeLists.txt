if (GOS_PID_ARDUINO_BASED_TUNING)
  add_subdirectory(libarduinobasedautotuning)
endif (GOS_PID_ARDUINO_BASED_TUNING)

if (GOS_PID_TOOLKIT_CPP)
  add_subdirectory(libpidtoolkit)
  add_subdirectory(libpidtoolkittune)
  add_subdirectory(libpidtoolkitpid)
endif (GOS_PID_TOOLKIT_CPP)
