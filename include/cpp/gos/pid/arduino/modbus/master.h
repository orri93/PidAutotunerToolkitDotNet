#ifndef GOS_PID_ARDUINO_MODBUS_MASTER_H_
#define GOS_PID_ARDUINO_MODBUS_MASTER_H_

#define GOT_PI_FORCE_OFF                    0
#define GOT_PI_FORCE_IDLE                   1
#define GOT_PI_FORCE_MANUAL                 2
#define GOT_PI_FORCE_AUTO                   3
#define GOT_PI_FORCE_MAXIMUM                3

#include <string>

#include <gos/pid/arduino/types.h>
#include <gos/pid/arduino/modbus/types.h>

namespace gos {
namespace pid {
namespace arduino {
namespace modbus {
namespace master {

namespace report {
namespace error {
::gos::pid::toolkit::type::error_number errorno();
std::string last();
} // namespace error
} // namespace report

::gos::pid::arduino::modbus::types::result initialize(
  const char* device,
  const int& baud,
  const int& slaveid,
  const char& parity = 'N',
  const int& data_bit = 8,
  const int& stop_bit = 1);

::gos::pid::arduino::modbus::types::result connect();

::gos::pid::arduino::modbus::types::result disconnect();

::gos::pid::arduino::modbus::types::result shutdown();

namespace read {
::gos::pid::arduino::modbus::types::result input(
  ::gos::pid::arduino::modbus::types::registry::Input& input);
::gos::pid::arduino::modbus::types::result holding(
  ::gos::pid::arduino::modbus::types::registry::Holding& holding);
} // namespace read
namespace write {
::gos::pid::arduino::modbus::types::result holding(
  const ::gos::pid::arduino::modbus::types::registry::Holding& holding);
::gos::pid::arduino::modbus::types::result interval(
  const ::gos::pid::arduino::types::Unsigned& interval);
::gos::pid::arduino::modbus::types::result manual(
  const ::gos::pid::arduino::types::Unsigned& manual);
::gos::pid::arduino::modbus::types::result setpoint(
  const ::gos::pid::arduino::types::Real& setpoint);
::gos::pid::arduino::modbus::types::result kp(
  const ::gos::pid::arduino::types::Real& kp);
::gos::pid::arduino::modbus::types::result ki(
  const ::gos::pid::arduino::types::Real& ki);
::gos::pid::arduino::modbus::types::result kd(
  const ::gos::pid::arduino::types::Real& kd);
::gos::pid::arduino::modbus::types::result tuning(
  const ::gos::pid::arduino::types::Real& kp,
  const ::gos::pid::arduino::types::Real& ki);
::gos::pid::arduino::modbus::types::result tuning(
  const ::gos::pid::arduino::types::Real& kp,
  const ::gos::pid::arduino::types::Real& ki,
  const ::gos::pid::arduino::types::Real& kd);
::gos::pid::arduino::modbus::types::result sensor(
  const ::gos::pid::arduino::types::Real& minimum,
  const ::gos::pid::arduino::types::Real& maximum);
::gos::pid::arduino::modbus::types::result time(
  const ::gos::pid::arduino::types::Unsigned& tuning);
::gos::pid::arduino::modbus::types::result force(
  const ::gos::pid::arduino::types::Unsigned& force);
} // namespace write

} // namespace master
} // namespace modbus
} // namespace arduino
} // namespace pid
} // namespace gos

#endif
