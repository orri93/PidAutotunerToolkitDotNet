#ifndef GOS_PID_ARDUINO_AUTOTUNING_PARAMETERS_H_
#define GOS_PID_ARDUINO_AUTOTUNING_PARAMETERS_H_

#include <gos/pid/arduino/autotuning/arduinobasedautotuninglibrary.h>

struct ARDUINOBASEDPIDAUTOTUNINGDLL_LIBRARY AutotuningParameters {
  AutotuningParameters();
  int MaximumPeakCount;
};

#endif
