#ifndef GOS_PID_TUNING_OPTIONS_H_
#define GOS_PID_TUNING_OPTIONS_H_

#include <boost/program_options.hpp>

#define GOS_ARDT_MOD_SD "sd"

#define GOS_ARDT_MOD_MIN_KP "min-kp"
#define GOS_ARDT_MOD_MAX_KP "max-kp"
#define GOS_ARDT_MOD_MIN_KI "min-ki"
#define GOS_ARDT_MOD_MAX_KI "max-ki"

#define GOS_ARDT_MOD_WINDOW "window"
#define GOS_ARDT_MOD_STABLE_DURATION "stable-duration"
#define GOS_ARDT_MOD_BASE_LINE "base-line"
#define GOS_ARDT_MOD_TUNING_OUTPUT "tuning-output"

#define GOS_ARDT_DEFAULT_SEPARATOR ","

#define GOS_ARDT_DEFAULT_WINDOW 15
#define GOS_ARDT_DEFAULT_STABLE_DURATION 15

#define GOS_ARDT_DEFAULT_SD 0.125F

#define GOS_ARDT_DEFAULT_MIN_KP 1.0F
#define GOS_ARDT_DEFAULT_MAX_KP 5.0F
#define GOS_ARDT_DEFAULT_MIN_KI 0.001F
#define GOS_ARDT_DEFAULT_MAX_KI 0.01F

#define GOS_ARDT_DEFAULT_TUNING_OUTPUT "tuning.csv"

namespace gos {
namespace pid {
namespace tuning {
namespace options {

void create(::boost::program_options::options_description& description);

} // namespace options
} // namespace tuning
} // namespace pid
} // namespace gos

#endif
