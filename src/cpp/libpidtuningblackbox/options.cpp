#include <gos/pid/arduino/types.h>

#include <gos/pid/tuning/options.h>
#include <gos/pid/tuning/setting.h>

namespace po = ::boost::program_options;

namespace gp = ::gos::pid;
namespace gpat = ::gos::pid::arduino::types;
namespace gpt = ::gos::pid::tuning;
namespace gpts = ::gos::pid::tuning::setting;

namespace gos {
namespace pid {
namespace tuning {
namespace options {

void create(po::options_description& description) {
  description.add_options()
    (GOS_ARDT_MOD_SD, po::value(&(gpts::parameters.Sd))
      ->default_value(GOS_ARDT_DEFAULT_SD),
      "standard deviation for the black box tuning")
    (GOS_ARDT_MOD_MIN_KP, po::value(&(gpts::parameters.Kp.lowest))
      ->default_value(GOS_ARDT_DEFAULT_MIN_KP),
      "minimum Kp value for the black box tuning")
    (GOS_ARDT_MOD_MAX_KP, po::value(&(gpts::parameters.Kp.highest))
      ->default_value(GOS_ARDT_DEFAULT_MAX_KP),
      "minimum Kp value for the black box tuning")
    (GOS_ARDT_MOD_MIN_KI, po::value(&(gpts::parameters.Ki.lowest))
      ->default_value(GOS_ARDT_DEFAULT_MIN_KI),
      "minimum Ki value for the black box tuning")
    (GOS_ARDT_MOD_MAX_KI, po::value(&(gpts::parameters.Ki.highest))
      ->default_value(GOS_ARDT_DEFAULT_MAX_KI),
      "minimum Ki value for the black box tuning")
    (GOS_ARDT_MOD_BASE_LINE, po::value<gpat::Real>(),
      "base line for the black box tuning")
    (GOS_ARDT_MOD_TUNING_OUTPUT, po::value(&(gpts::output::file::path))
      ->default_value(GOS_ARDT_DEFAULT_TUNING_OUTPUT),
      "tuning output file path")
    (GOS_ARDT_MOD_WINDOW, po::value(&(gpts::window::size))
      ->default_value(GOS_ARDT_DEFAULT_WINDOW),
      "running window size for tuning")
    (GOS_ARDT_MOD_STABLE_DURATION, po::value(&(gpts::stable::duration::minutes))
      ->default_value(GOS_ARDT_DEFAULT_STABLE_DURATION),
      "stable time for tuning in minutes");
}

} // namespace options
} // namespace tuning
} // namespace pid
} // namespace gos
