#include <gos/pid/tuning/output.h>
#include <gos/pid/arduino/modbus/options.h>

namespace po = ::boost::program_options;

namespace gptt = ::gos::pid::tuning::types;

namespace gpamt = ::gos::pid::arduino::modbus::types;

namespace gos {
namespace pid {
namespace tuning {
namespace output {

void header(
  std::ostream& stream,
  const std::string& separator,
  const bool& isinternal,
  po::variables_map& map,
  const gptt::TuningMode& mode) {
  bool iswithround = mode == gptt::TuningMode::blackbox;

  stream << "time";
  if (iswithround) {
    stream << separator << "round";
  }
  stream << separator << "status";
  switch (mode) {
  case gptt::TuningMode::blackbox:
    stream << separator << "kp";
    stream << separator << "ki";
    break;
  default:
    if (map.count(GOS_ARDT_MOD_KP)) {
      stream << separator << "kp";
    }
    if (map.count(GOS_ARDT_MOD_KI)) {
      stream << separator << "ki";
    }
    break;
  }
  if (map.count(GOS_ARDT_MOD_KD)) {
    stream << separator << "kd";
  }
  if (map.count(GOS_ARDT_MOD_MANUAL)) {
    stream << separator << "manual";
  }
  if (map.count(GOS_ARDT_MOD_SETPOINT)) {
    stream << separator << "setpoint";
  }
  stream << separator << "output" << separator << "temperature";
  if (isinternal) {
    stream
      << separator << "error"
      << separator << "integral"
      << separator << "derivative";
  }
  stream << std::endl;
}

void result(
  std::ostream& stream,
  const gpamt::registry::Input& input,
  const gpamt::registry::Holding& holding,
  const gptt::Initialized& initialized,
  const gptt::Variables& variables,
  const std::string& separator,
  const bool& isinternal,
  const bool& issuccess,
  po::variables_map& map,
  const gptt::TuningMode& mode) {

  if (issuccess) {
    stream << separator << input.Status;
  } else {
    stream << separator << -1;
  }

  switch (mode) {
  case gptt::TuningMode::blackbox:
    stream << separator << variables.Kp;
    stream << separator << variables.Ki;
    break;
  default:
    if (initialized.Kp.is_initialized()) {
      stream << separator << holding.Kp;
    }
    if (initialized.Ki.is_initialized()) {
      stream << separator << holding.Ki;
    }
    break;
  }
  if (initialized.Kd.is_initialized()) {
    stream << separator << holding.Kd;
  }
  if (initialized.Manual.is_initialized()) {
    stream << separator << holding.Manual;
  }
  if (initialized.Setpoint.is_initialized()) {
    stream << separator << holding.Setpoint;
  }

  if (issuccess) {
    stream
      << separator << input.Output
      << separator << input.Temperature;
    if (isinternal) {
      stream << separator << input.Error
        << separator << input.Integral
        << separator << input.Derivative;
    }
  } else {
    stream << separator << separator;
    if (isinternal) {
      stream << separator << separator << separator;
    }
  }
  stream << std::endl;
}

} // namespace output
} // namespace tuning
} // namespace pid
} // namespace gos
