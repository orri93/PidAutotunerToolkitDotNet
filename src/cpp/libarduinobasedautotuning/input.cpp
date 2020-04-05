#ifdef _USRDLL
#include "pch.h"
#endif
#include <gos/pid/arduino/autotuning/input.h>

AutotuningInput::AutotuningInput() :
  ControlType(ControlType::PID),
  NoiseBand(0.5),
  OutputStep(30.0),
  Lookback(10) {
}
