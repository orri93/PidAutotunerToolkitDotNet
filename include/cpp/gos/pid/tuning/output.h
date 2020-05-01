#ifndef GOS_PID_TUNING_OUTPUT_H_
#define GOS_PID_TUNING_OUTPUT_H_

#include <ostream>
#include <string>

#include <boost/program_options.hpp>

#include <gos/pid/arduino/modbus/types.h>

#include <gos/pid/tuning/types.h>

namespace gos {
namespace pid {
namespace tuning {
namespace output {

void header(
  std::ostream& stream,
  const std::string& separator,
  const bool& isinternal,
  ::boost::program_options::variables_map& map,
  const ::gos::pid::tuning::types::TuningMode& mode);

void result(
  std::ostream& stream,
  const ::gos::pid::arduino::modbus::types::registry::Input& input,
  const ::gos::pid::arduino::modbus::types::registry::Holding& holding,
  const ::gos::pid::tuning::types::Initialized& initialized,
  const ::gos::pid::tuning::types::Variables& variables,
  const std::string& separator,
  const bool& isinternal,
  const bool& issuccess,
  ::boost::program_options::variables_map& map,
  const ::gos::pid::tuning::types::TuningMode& mode);

} // namespace output
} // namespace tuning
} // namespace pid
} // namespace gos

#endif
