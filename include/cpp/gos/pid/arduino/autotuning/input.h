#ifndef GOS_PID_ARDUINO_AUTOTUNING_INPUT_H_
#define GOS_PID_ARDUINO_AUTOTUNING_INPUT_H_

#ifdef ARDUINOBASEDAUTOTUNINGDLL
#include "arduinobasedautotuninglibrary.h"
#else
#define ARDUINOBASEDPIDAUTOTUNINGDLL_LIBRARY
#endif
#include <gos/pid/arduino/autotuning/type.h>

struct ARDUINOBASEDPIDAUTOTUNINGDLL_LIBRARY AutotuningInput {
  AutotuningInput();
  ControlType ControlType;
  bool Autotune;
  double Input;
  double Output;
  double OutputStep;
  double NoiseBand;
  int Lookback;
  unsigned int CurrentTick;
};

#endif
