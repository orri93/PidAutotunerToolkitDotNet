#ifndef GOS_PID_ARDUINO_AUTOTUNING_INPUT_H_
#define GOS_PID_ARDUINO_AUTOTUNING_INPUT_H_

#include <gos/pid/arduino/autotuning/arduinobasedautotuninglibrary.h>
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
