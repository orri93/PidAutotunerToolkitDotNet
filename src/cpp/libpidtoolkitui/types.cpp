#include <gos/pid/ui/types.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace types {

namespace to {
std::string string(const status& status) {
  switch (status) {
  case status::undefined:
    return "Undefined";
  case status::connected:
    return "Connected";
  case status::connecting:
    return "Connecting";
  case status::disconnected:
    return "Disconnected";
  case status::disconnecting:
    return "Disconnecting";
  default:
    return "Unknown";
  }
}
} // namespace to

} // namespace types
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos