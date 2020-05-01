#include <string>

#include <gos/pid/arduino/modbus/options.h>
#include <gos/pid/arduino/types.h>

namespace po = ::boost::program_options;

namespace gpa = ::gos::pid::arduino;
namespace gpat = ::gos::pid::arduino::types;

namespace gos {
namespace pid {
namespace arduino {
namespace modbus {
namespace options {

void create(po::options_description& description) {
  description.add_options()
    (GOS_ARDT_MOD_MANUAL, po::value<gpat::Unsigned>(), "manual value")
    (GOS_ARDT_MOD_FORCE, po::value<gpat::Unsigned>(), "force")
    (GOS_ARDT_MOD_FINAL, po::value<gpat::Unsigned>(), "final force")
    (GOS_ARDT_MOD_SETPOINT, po::value<gpat::Real>(), "setpoint")
    (GOS_ARDT_MOD_KP, po::value<gpat::Real>(), "kp")
    (GOS_ARDT_MOD_KI, po::value<gpat::Real>(), "ki")
    (GOS_ARDT_MOD_KD, po::value<gpat::Real>(), "kd");
}

} // namespace options
} // namespace modbus
} // namespace arduino
} // namespace pid
} // namespace gos