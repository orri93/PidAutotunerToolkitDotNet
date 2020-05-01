#ifndef GOS_PID_TUNING_SETTING_H_
#define GOS_PID_TUNING_SETTING_H_

#include <string>

#include <gos/pid/arduino/types.h>
#include <gos/pid/tuning/types.h>

namespace gos {
namespace pid {
namespace tuning {
namespace setting {

extern ::gos::pid::tuning::types::Parameters parameters;

namespace output {
namespace file {
extern std::string path;
}
}

namespace window {
extern size_t size;
}

namespace stable {
namespace duration {
extern ::gos::pid::arduino::types::Unsigned minutes;
}
}

} // namespace setting
} // namespace tuning
} // namespace pid
} // namespace gos

#endif
