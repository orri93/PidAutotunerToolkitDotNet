#ifndef GOS_PID_ARDUINO_AUTOTUNING_PARAMETERS_H_
#define GOS_PID_ARDUINO_AUTOTUNING_PARAMETERS_H_

#ifdef ARDUINOBASEDAUTOTUNINGDLL
#include "arduinobasedautotuninglibrary.h"
#else
#define ARDUINOBASEDPIDAUTOTUNINGDLL_LIBRARY
#endif

struct ARDUINOBASEDPIDAUTOTUNINGDLL_LIBRARY AutotuningParameters {
  AutotuningParameters();
  int MaximumPeakCount;
};

#endif
