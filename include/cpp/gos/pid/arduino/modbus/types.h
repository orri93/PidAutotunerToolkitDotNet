#ifndef GOS_PID_ARDUINO_MODBUS_TYPES_H_
#define GOS_PID_ARDUINO_MODBUS_TYPES_H_

#include <memory>

#include <gos/pid/arduino/types.h>

namespace gos {
namespace pid {
namespace arduino {
namespace modbus {
namespace types {

enum class result {
  undefiend,
  success,
  failure,
  fatal,
  uninitialized,
  disconnected
};

namespace registry {

struct Input {
  ::gos::pid::arduino::types::Unsigned Output;
  ::gos::pid::arduino::types::Real Temperature;
  ::gos::pid::arduino::types::Real Error;
  ::gos::pid::arduino::types::Real Integral;
  ::gos::pid::arduino::types::Real Derivative;
  ::gos::pid::arduino::types::Unsigned Status;
};

struct Holding {
  ::gos::pid::arduino::types::Unsigned Interval;
  ::gos::pid::arduino::types::Unsigned Manual;
  ::gos::pid::arduino::types::Real Setpoint;
  ::gos::pid::arduino::types::Real Kp;
  ::gos::pid::arduino::types::Real Ki;
  ::gos::pid::arduino::types::Real Kd;
  ::gos::pid::arduino::types::Real SensorMinimum;
  ::gos::pid::arduino::types::Real SensorMaximum;
  ::gos::pid::arduino::types::Unsigned TimeTune;
  ::gos::pid::arduino::types::Unsigned Force;
};

typedef std::unique_ptr<Input> InputPointer;
typedef std::unique_ptr<Holding> HoldingPointer;

} // namespace registry


} // namespace types
} // namespace modbus
} // namespace arduino
} // namespace pid
} // namespace gos

#endif
