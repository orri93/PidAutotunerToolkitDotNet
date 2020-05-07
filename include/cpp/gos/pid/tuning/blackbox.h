#ifndef GOS_PID_TUNING_BLACK_BOX_H_
#define GOS_PID_TUNING_BLACK_BOX_H_

#include <ostream>
#include <memory>

#include <boost/program_options.hpp>

#include <gos/pid/arduino/modbus/types.h>

#include <gos/pid/toolkit/types.h>
#include <gos/pid/arduino/types.h>
#include <gos/pid/tuning/types.h>
#include <gos/pid/tuning/notify.h>

#define GOS_PID_TUNING_BLACK_BOX_SEED_TYPE int
#define GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE double 

namespace gos {
namespace pid {
namespace tuning {
namespace black {
namespace box {

struct Variables {
  ::gos::pid::arduino::types::Real Kd;
  ::gos::pid::arduino::types::Real PeakError;
  ::gos::pid::arduino::types::Real StableError;
  ::gos::pid::arduino::types::Real ErrorVariance;
  ::gos::pid::arduino::types::Real Setpoint;
  ::gos::pid::toolkit::type::Time StableTime;
  GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE StartRoundElapsed;
  GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE OverElapsed;
  GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE UnderElapsed;
  GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE StableElapsed;
  GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE CoolingElapsed;
  bool IsRoundStarting;
  bool IsOver;
  bool IsUnder;
  bool IsStable;
  bool IsCooling;
  bool IsCoolingFinished;
  bool IsRoundFinished;
  bool IsRoundEvaluated;
  bool IsDataReady;
  size_t Count;
};

typedef std::unique_ptr<Variables> VariablesPointer;

namespace notify {
bool handover(::gos::pid::tuning::NotifyPointer& notify);
bool recover(::gos::pid::tuning::NotifyPointer& notify);
}

void initialize(
  gos::pid::tuning::types::Variables& variables,
  Variables& black,
  const gos::pid::tuning::types::Parameters& parameters,
  const ::gos::pid::arduino::types::Real& kp,
  const ::gos::pid::arduino::types::Real& ki);

void initialize(
  ::gos::pid::tuning::types::Variables& variables,
  Variables& black,
  const ::gos::pid::tuning::types::Parameters& parameters);

void shutdown();

void load(
  Variables& variables,
  const ::gos::pid::tuning::types::Initialized& initialized,
  const ::gos::pid::arduino::modbus::types::registry::Holding& holding,
  const std::string& separator,
  const bool& isinternal);

void cycle(
  int& round,
  ::gos::pid::tuning::types::Variables& variables,
  Variables& black,
  ::gos::pid::tuning::types::EvaluationPointer& best,
  ::gos::pid::tuning::types::Parameters& parameters,
  const ::gos::pid::arduino::modbus::types::registry::Input& input,
  const GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE& elapsed,
  const ::gos::pid::toolkit::type::Time& time,
  const std::string& separator,
  const bool& issuccessful,
  const bool& isinternal);

void seed(const GOS_PID_TUNING_BLACK_BOX_SEED_TYPE& seed);

namespace random {
::gos::pid::arduino::types::Real next();
}

namespace compute {
void newtunings(const
  ::gos::pid::tuning::types::Parameters& parameters,
  ::gos::pid::tuning::types::Variables& variables);
} // namespace compute

::gos::pid::arduino::types::Real evaluate(
  const ::gos::pid::arduino::types::Real& peakerror,
  const ::gos::pid::arduino::types::Real& stableerror);

void evaluate(::gos::pid::tuning::types::Evaluation& evaluation);
void replace(
  ::gos::pid::tuning::types::EvaluationPointer& last,
  const ::gos::pid::tuning::types::Evaluation& current);

namespace initial {
namespace apply {
bool tuning(
  ::gos::pid::tuning::types::Initialized& initialized,
  ::boost::program_options::variables_map& map,
  ::gos::pid::tuning::types::Variables& variables,
  Variables& black,
  const ::gos::pid::tuning::types::Parameters& parameters,
  const ::gos::pid::tuning::types::TuningMode& mode);
} // namespace apply
} // namespace inital

namespace output {
void header(
  std::ostream& stream,
  const std::string& separator,
  const bool& isinternal);
void result(
  std::ostream& stream,
  const ::gos::pid::tuning::types::Variables& variables,
  const ::gos::pid::tuning::black::box::Variables& black,
  const ::gos::pid::tuning::types::Evaluation& evaluation,
  const std::string& separator,
  const bool& isinternal);
} // namespace output

} // namespace box
} // namespace black
} // namespace tuning
} // namespace pid
} // namespace gos

#endif
