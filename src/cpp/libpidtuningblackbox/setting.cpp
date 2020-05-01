#include <gos/pid/tuning/setting.h>

namespace gpat = ::gos::pid::arduino::types;
namespace gptt = ::gos::pid::tuning::types;

namespace gos {
namespace pid {
namespace tuning {
namespace setting {

gptt::Parameters parameters;

namespace output {
namespace file {
std::string path;
}
}

namespace window {
size_t size;
}

namespace stable {
namespace duration {
gpat::Unsigned minutes;
}
}

} // namespace setting
} // namespace tuning
} // namespace pid
} // namespace gos
