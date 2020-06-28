#include <iostream>
#include <random>
#include <memory>
#include <limits>
#include <mutex>

#include <gos/pid/toolkit/utilities.h>
#include <gos/pid/toolkit/setting.h>

#include <gos/pid/arduino/modbus/options.h>
#include <gos/pid/arduino/modbus/master.h>
#include <gos/pid/arduino/modbus/retry.h>

#include <gos/pid/tuning/options.h>
#include <gos/pid/tuning/blackbox.h>
#include <gos/pid/tuning/setting.h>
#include <gos/pid/tuning/types.h>

#define GOS_ARDUINO_TOOLS_MASTER_BASE_LINE_ADDITION 5.0F

namespace po = ::boost::program_options;

namespace gp = ::gos::pid;
namespace gpt = ::gos::pid::toolkit;
namespace gpto = ::gos::pid::toolkit::setting;
namespace gptu = ::gos::pid::toolkit::utilities;

namespace gpa = ::gos::pid::arduino;
namespace gpam = ::gos::pid::arduino::modbus;
namespace gpat = ::gos::pid::arduino::types;

namespace gptt = ::gos::pid::tuning::types;
namespace gpts = ::gos::pid::tuning::setting;

namespace gos {
namespace pid {
namespace tuning {
namespace black {
namespace box {

namespace detail{
static gpa::types::Statistics statistics;
static gpa::types::Window window;
namespace output {
namespace stream {
static gpt::type::OutputStreamPointer pointer;
}
namespace file {
namespace stream {
static gpt::type::OutputFileStreamPointer pointer;
}
}
}
}

const gpat::Real PeakFactor = 1.0F;
const gpat::Real StableFactor = 1.0F;

typedef ::std::default_random_engine Engine;
typedef ::std::unique_ptr<Engine> EnginePointer;
typedef ::std::normal_distribution<gpat::Real> Distribution;
typedef ::std::unique_ptr<Distribution> DistributionPointer;

static EnginePointer _engine;
static DistributionPointer _distribution;

static const gpat::Real Mean = 0.0;

namespace notify {
static gp::tuning::NotifyPointer _instance;
static std::mutex _lock;
bool handover(::gos::pid::tuning::NotifyPointer& notify) {
  std::lock_guard<std::mutex> guard(_lock);
  if (!_instance && notify) {
    _instance = std::move(notify);
    if (_instance) {
      return true;
    }
  }
  return false;
}

bool recover(::gos::pid::tuning::NotifyPointer& notify) {
  std::lock_guard<std::mutex> guard(_lock);
  if (!notify && _instance) {
    notify = std::move(_instance);
    if (notify) {
      return true;
    }
  }
  return false;
}
}

void initialize(
  gptt::Variables& variables,
  Variables& black,
  const gptt::Parameters& parameters,
  const gpat::Real& kp,
  const gpat::Real& ki) {
  variables.Kp = kp;
  variables.Ki = ki;
  _engine = ::std::make_unique<Engine>();
  _distribution = ::std::make_unique<Distribution>(Mean, parameters.Sd);
  black.IsRoundStarting = true;
  black.IsOver = false;
  black.IsUnder = false;
  black.IsStable = false;
  black.IsCooling = false;
  black.IsCoolingFinished = false;
  black.IsRoundFinished = false;
  black.IsRoundEvaluated = false;
  black.IsDataReady = false;
  detail::window.set(gpts::window::size);
}

void initialize(
  gptt::Variables& variables,
  Variables& black,
  const gptt::Parameters& parameters) {
  initialize(
    variables,
    black,
    parameters,
    gptu::midpoint(parameters.Kp),
    gptu::midpoint(parameters.Ki));
}

void shutdown() {
  if (detail::output::file::stream::pointer) {
    detail::output::file::stream::pointer->flush();
    detail::output::file::stream::pointer->close();
  }
  if (gpa::modbus::master::retry::write::force(GOT_PI_FORCE_IDLE) ==
    gpam::types::result::success) {
    std::lock_guard<std::mutex> guard(notify::_lock);
    if (notify::_instance) {
      notify::_instance->notifyForce(GOT_PI_FORCE_IDLE);
    }
  }
}

void load(
  Variables& variables,
  const gptt::Initialized& initialized,
  const gpam::types::registry::Holding& holding,
  const std::string& separator,
  const bool& isinternal) {
  if (initialized.Kd.is_initialized()) {
    variables.Kd = initialized.Kd.get();
  } else {
    variables.Kd = holding.Kd;
  }
  if (initialized.Setpoint.is_initialized()) {
    variables.Setpoint = initialized.Setpoint.get();
  } else {
    variables.Setpoint = holding.Setpoint;
  }
  detail::output::file::stream::pointer = std::make_unique<std::ofstream>();
  detail::output::file::stream::pointer->open(
    gp::tuning::setting::output::file::path, std::ios::out | std::ios::trunc);
  detail::output::stream::pointer = std::make_unique<std::ostream>(
    detail::output::file::stream::pointer->rdbuf());

  output::header(*detail::output::stream::pointer, separator, isinternal);
}

void cycle(
  int& round,
  gptt::Variables& variables,
  Variables& black,
  gptt::EvaluationPointer& best,
  gptt::Parameters& parameters,
  const gpam::types::registry::Input& input,
  const GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE& elapsed,
  const gpt::type::Time& time,
  const std::string& separator,
  const bool& issuccessful,
  const bool& isinternal) {
  if (black.IsRoundStarting) {
    if (gpto::isverbose()) {
      std::cout << "Round Starting at " << elapsed
        << " with Kp as " << variables.Kp
        << " and Ki as " << variables.Ki << std::endl;
    }
    black.StartRoundElapsed = elapsed;
    black.IsOver = false;
    black.IsUnder = false;
    black.IsStable = false;
    black.IsCooling = false;
    black.IsCoolingFinished = false;
    black.IsRoundStarting = false;
    black.IsRoundFinished = false;
    black.IsRoundEvaluated = false;
    black.IsDataReady = false;
    variables.Minimum = std::numeric_limits<gpat::Real>::max();
    variables.Maximum = std::numeric_limits<gpat::Real>::lowest();
    detail::statistics.clear();
    detail::window.clear();
  }
  if (issuccessful) {
    if (!parameters.BaseLine.is_initialized()) {
      parameters.BaseLine = input.Temperature +
        GOS_ARDUINO_TOOLS_MASTER_BASE_LINE_ADDITION;
      if (gpto::isverbose()) {
        std::cout << "Base line is set to " << parameters.BaseLine.get()
          << " at " << elapsed << std::endl;
      }
    }
    if (input.Temperature > variables.Maximum) {
      if (gpto::isverbose()) {
        std::cout << "New Maximum " << input.Temperature
          << " at " << elapsed << std::endl;
      }
      variables.Maximum = input.Temperature;
    }
    if (input.Temperature < variables.Minimum) {
      if (gpto::isverbose()) {
        std::cout << "New Minimum " << input.Temperature
          << " at " << elapsed << std::endl;
      }
      variables.Minimum = input.Temperature;
    }
    detail::window.add(input.Temperature);
    variables.Mean = detail::window.mean();

    if (!black.IsRoundFinished) {
      if (black.IsCooling) {
        black.IsCoolingFinished = variables.Mean < parameters.BaseLine.get();
        if (black.IsCoolingFinished) {
          if (gpto::isverbose()) {
            std::cout << "Cooling Finished at " << elapsed << std::endl;
          }
        }
      } else {
        if (black.IsStable) {
          detail::statistics.add(input.Temperature);
          gpt::type::Duration curstableduration = time - black.StableTime;
          if (curstableduration >
            std::chrono::minutes(gpts::stable::duration::minutes)) {
            /* Stop the controller and force zero */
            if (gpam::master::retry::write::force(GOT_PI_FORCE_IDLE) ==
              gpam::types::result::success) {
                {
                  std::lock_guard<std::mutex> guard(notify::_lock);
                  if (notify::_instance) {
                    notify::_instance->notifyForce(GOT_PI_FORCE_IDLE);
                  }
                }
              if (gpto::isverbose()) {
                std::cout << "Stable Duration Completed at "
                  << elapsed << " data are ready" << std::endl;
              }
              black.IsCooling = true;
              black.IsDataReady = true;
              black.CoolingElapsed = elapsed;
            }
          }
        } else {
          if (black.IsUnder) {
            if (gpto::isverbose()) {
              std::cout << "Stable at " << elapsed << std::endl;
            }
            black.StableTime = time;
            black.StableElapsed = elapsed;
            black.IsStable = true;
          } else {
            if (black.IsOver) {
              black.IsUnder = variables.Mean < black.Setpoint;
              if (black.IsUnder) {
                if (gpto::isverbose()) {
                  std::cout << "Under at " << elapsed << std::endl;
                }
                black.UnderElapsed = elapsed;
              }
            } else {
              black.IsOver = variables.Mean > black.Setpoint;
              if (black.IsOver) {
                if (gpto::isverbose()) {
                  std::cout << "Over at " << elapsed << std::endl;
                }
                black.OverElapsed = elapsed;
              }
            }
          }
        }
      }
    }
  }

  if (black.IsDataReady) {
    if (!black.IsRoundEvaluated) {
      gpat::Real difference;
      gpat::Real differencesqrtsum = 0.0;
      for (const gpat::Real value : detail::statistics.vector()) {
        difference = black.Setpoint - value;
        differencesqrtsum += difference * difference;
      }

      black.Count = detail::statistics.count();
      black.ErrorVariance = differencesqrtsum /
        static_cast<gpat::Real>(black.Count);
      black.StableError = ::sqrtf(black.ErrorVariance);
      black.PeakError = variables.Maximum - black.Setpoint;
      if (gpto::isverbose()) {
        std::cout << "Data Calculation: Stable Count is " << black.Count
          << ", Squared Sum of Stable Errors is " << differencesqrtsum
          << ", Stable Error Variance is " << black.ErrorVariance
          << ", Stable Error SD is " << black.StableError
          << " and Peak Error is " << black.PeakError << std::endl;
      }

      gp::tuning::types::Evaluation evaluation;
      evaluation.Kp = variables.Kp;
      evaluation.Ki = variables.Ki;
      evaluation.Kd = black.Kd;
      evaluation.PeakError = black.PeakError;
      evaluation.StableError = black.StableError;
      evaluate(evaluation);

      if (best) {
        if (evaluation.Performance < best->Performance) {
          if (gpto::isverbose()) {
            std::cout << "The performance " << evaluation.Performance
              << " for the current round was "
              "better than the previous " << best->Performance << ","
              " Kp is " << variables.Kp <<
              " and Ki is " << variables.Ki << std::endl;
          }
          replace(best, evaluation);
        } else {
          /* May setting the Kp and Ki to the last best values a new tuning 
             Parameters will be generated from them */
          variables.Kp = best->Kp;
          variables.Ki = best->Ki;
          if (gpto::isverbose()) {
            std::cout << "The performance " << evaluation.Performance
              << " for the current round was not "
              "better than the previous " << best->Performance << ","
              " Kp is " << variables.Kp <<
              " and Ki is " << variables.Ki << std::endl;
          }
        }
      } else {
        if (gpto::isverbose()) {
          std::cout << "First evaluated performance "
            << evaluation.Performance << ","
            " Kp is " << variables.Kp <<
            " and Ki is " << variables.Ki << std::endl;
        }
        replace(best, evaluation);
      }
      compute::newtunings(parameters, variables);
      if (gpto::isverbose()) {
        std::cout << "New tuning parameters generated with Kp as "
          << variables.Kp << " and Ki as " << variables.Ki << std::endl;
      }

      output::result(
        *detail::output::stream::pointer,
        variables,
        black,
        evaluation,
        separator,
        isinternal);

      detail::output::file::stream::pointer->flush();

      black.IsRoundEvaluated = true;
    }
  }

  if (black.IsCoolingFinished) {
    bool updateresult =
      gpam::master::retry::write::tuning(variables.Kp, variables.Ki)
      == gpam::types::result::success &&
      gpam::master::retry::write::force(GOT_PI_FORCE_AUTO)
      == gpam::types::result::success;
    if (updateresult) {
      {
        std::lock_guard<std::mutex> guard(notify::_lock);
        if (notify::_instance) {
          notify::_instance->notifyKp(variables.Kp);
          notify::_instance->notifyKi(variables.Ki);
          notify::_instance->notifyForce(GOT_PI_FORCE_AUTO);
        }
      }
      if (gpto::isverbose()) {
        std::cout << "The tuning parameters with Kp as " << variables.Kp
          << " and " << variables.Ki
          << " where successfully writen though Modbus" << std::endl;
      }
      round++;
      black.IsRoundStarting = true;
    }
  }
}

void seed(const GOS_PID_TUNING_BLACK_BOX_SEED_TYPE& seed) {
  if (_engine) {
    _engine->seed(seed);
  }
}

namespace random {
gpat::Real next() {
  return (*_distribution)(*_engine);
}
}

namespace compute {
void newtunings(const gptt::Parameters& parameters, gptt::Variables& variables) {
  gpat::Real newkp = variables.Kp + random::next() * gptu::scale(parameters.Kp);
  gpat::Real newki = variables.Ki + random::next() * gptu::scale(parameters.Ki);
  variables.Kp = gptu::restrict<gpat::Real>(parameters.Kp, newkp);
  variables.Ki = gptu::restrict<gpat::Real>(parameters.Ki, newki);
}
}

gpat::Real evaluate(const gpat::Real& peakerror, const gpat::Real& stableerror) {
  return PeakFactor * peakerror + StableFactor * stableerror;
}

void evaluate(::gos::pid::tuning::types::Evaluation& evaluation) {
  evaluation.Performance = evaluate(
    evaluation.PeakError,
    evaluation.StableError);
}
void replace(gptt::EvaluationPointer& last, const gptt::Evaluation& current) {
  if (!last) {
    last = std::make_unique<gptt::Evaluation>();
  }
  last->Kp = current.Kp;
  last->Ki = current.Ki;
  last->Kd = current.Kd;
  last->PeakError = current.PeakError;
  last->StableError = current.StableError;
  last->Performance = current.Performance;
}

namespace initial {
namespace apply {
bool tuning(
  gptt::Initialized& initialized,
  po::variables_map& map,
  gptt::Variables& variables,
  Variables& black,
  const gptt::Parameters& parameters,
  const gptt::TuningMode& mode) {

  if (map.count(GOS_ARDT_MOD_KP) > 0) {
    initialized.Kp = map[GOS_ARDT_MOD_KP].as<gpat::Real>();
  }
  if (map.count(GOS_ARDT_MOD_KI) > 0) {
    initialized.Ki = map[GOS_ARDT_MOD_KI].as<gpat::Real>();
  }
  if (map.count(GOS_ARDT_MOD_KD) > 0) {
    initialized.Kd = map[GOS_ARDT_MOD_KD].as<gpat::Real>();
  }
  if (map.count(GOS_ARDT_MOD_MANUAL) > 0) {
    initialized.Manual =
      map[GOS_ARDT_MOD_MANUAL].as<gpat::Unsigned>();
  }
  if (map.count(GOS_ARDT_MOD_SETPOINT) > 0) {
    initialized.Setpoint =
      map[GOS_ARDT_MOD_SETPOINT].as<gpat::Real>();
  }

  switch (mode) {
  case gptt::TuningMode::blackbox:
    if (initialized.Kp.is_initialized() && initialized.Ki.is_initialized()) {
      initialize(
        variables,
        black,
        parameters,
        initialized.Kp.get(),
        initialized.Ki.get());
    } else {
      initialize(variables, black, parameters);
      initialized.Kp = variables.Kp;
      initialized.Ki = variables.Ki;
    }
    break;
  default:
    break;
  }

  if (
    initialized.Kp.is_initialized() &&
    initialized.Ki.is_initialized() &&
    initialized.Kd.is_initialized()) {
    if (gpam::master::retry::write::tuning(
      initialized.Kp.get(),
      initialized.Ki.get(),
      initialized.Kd.get()) != gpam::types::result::success) {
      return false;
    }
  } else {
    if (
      initialized.Kp.is_initialized() &&
      initialized.Ki.is_initialized()) {
      if (gpam::master::retry::write::tuning(
        initialized.Kp.get(),
        initialized.Ki.get()) != gpam::types::result::success) {
        return false;
      }
    } else {
      if (initialized.Kp.is_initialized()) {
        if (gpam::master::retry::write::kp(initialized.Kp.get())
          != gpam::types::result::success) {
          return false;
        }
      }
      if (initialized.Ki.is_initialized()) {
        if (gpam::master::retry::write::ki(initialized.Ki.get())
          != gpam::types::result::success) {
          return false;
        }
      }
    }
    if (initialized.Kd.is_initialized()) {
      if (gpam::master::retry::write::kd(initialized.Kd.get())
        != gpam::types::result::success) {
        return false;
      }
    }
  }

  if (initialized.Setpoint.is_initialized()) {
    if (gpam::master::retry::write::setpoint(initialized.Setpoint.get())
      != gpam::types::result::success) {
      return false;
    }
  } else if (initialized.Manual.is_initialized()) {
    if (gpam::master::retry::write::manual(initialized.Manual.get())
      != gpam::types::result::success) {
      return false;
    }
  }

  return true;

}
} // namespace apply
} // namespace inital

namespace output {
void header(
  std::ostream& stream,
  const std::string& separator,
  const bool& isinternal) {
  stream << "time" << separator << "round"
    << separator << "kp" << separator << "ki" << separator << "kd"
    << separator << "peak"
    << separator << "peak-error"
    << separator << "stable-error"
    << separator << "performance";
  if (isinternal) {
    stream
      << separator << "over"
      << separator << "under"
      << separator << "stable"
      << separator << "cooling"
      << separator << "count";
  }
  stream << std::endl;
}
void result(
  std::ostream& stream,
  const gptt::Variables& variables,
  const Variables& black,
  const gptt::Evaluation& evaluation,
  const std::string& separator,
  const bool& isinternal) {
  stream << black.StartRoundElapsed << separator << variables.Round
    << separator << variables.Kp
    << separator << variables.Ki
    << separator << black.Kd
    << separator << variables.Maximum
    << separator << black.PeakError
    << separator << black.StableError
    << separator << evaluation.Performance;
  if (isinternal) {
    stream
      << separator << black.OverElapsed
      << separator << black.UnderElapsed
      << separator << black.StableElapsed
      << separator << black.CoolingElapsed
      << separator << black.Count;
  }
  stream << std::endl;
}
} // namespace output

} // namespace box
} // namespace black
} // namespace tuning
} // namespace pid
} // namespace gos

