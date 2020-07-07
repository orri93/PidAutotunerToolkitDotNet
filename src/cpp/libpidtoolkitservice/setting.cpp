#include <sstream>

#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/service/setting.h>

namespace gpt = ::gos::pid::toolkit;
namespace gpts = ::gos::pid::toolkit::setting;

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace setting {
std::string address() {
  std::stringstream stream;
  stream << "tcp://" << gpt::setting::communication::mqtt::host
    << ":" << gpt::setting::communication::mqtt::port;
  return stream.str();
}
}
}
}
}
}