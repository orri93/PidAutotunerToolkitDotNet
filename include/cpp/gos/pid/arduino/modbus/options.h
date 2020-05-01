#ifndef GOS_PID_ARDUINO_MODBUS_OPTIONS_H_
#define GOS_PID_ARDUINO_MODBUS_OPTIONS_H_

#include <boost/program_options.hpp>

#define GOS_ARDT_MOD_MANUAL "manual"
#define GOS_ARDT_MOD_SETPOINT "setpoint"
#define GOS_ARDT_MOD_KP "kp"
#define GOS_ARDT_MOD_KI "ki"
#define GOS_ARDT_MOD_KD "kd"
#define GOS_ARDT_MOD_FORCE "force"
#define GOS_ARDT_MOD_FINAL "final"

#define GOS_ARDT_DEFAULT_MIN_KP 1.0F
#define GOS_ARDT_DEFAULT_MAX_KP 5.0F
#define GOS_ARDT_DEFAULT_MIN_KI 0.001F
#define GOS_ARDT_DEFAULT_MAX_KI 0.01F

namespace gos {
namespace pid {
namespace arduino {
namespace modbus {
namespace options {

void create(::boost::program_options::options_description& description);

} // namespace options
} // namespace modbus
} // namespace arduino
} // namespace pid
} // namespace gos

#endif
