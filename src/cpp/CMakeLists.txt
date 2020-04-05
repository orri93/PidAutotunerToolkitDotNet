if (GOS_PID_ARDUINO_BASED_TUNING)
  add_subdirectory(libarduinobasedautotuning)
endif (GOS_PID_ARDUINO_BASED_TUNING)

if (GOS_PID_TOOLKIT_CPP)
  add_subdirectory(libpidtoolkit)
endif (GOS_PID_TOOLKIT_CPP)
