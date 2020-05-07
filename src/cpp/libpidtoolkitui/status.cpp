#include <gos/pid/ui/status.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace status {

gptu::types::status convert(const gptu::item::Connection::Status& status) {
  switch (status) {
  case gptu::item::Connection::Status::PTC_UNDEFINED:
    return gptut::status::undefined;
  case gptu::item::Connection::Status::PTC_CONNECTED:
    return gptut::status::connected;
  case gptu::item::Connection::Status::PTC_CONNECTING:
    return gptut::status::connecting;
  case gptu::item::Connection::Status::PTC_DISCONNECTED:
    return gptut::status::disconnected;
  case gptu::item::Connection::Status::PTC_DISCONNECTING:
    return gptut::status::disconnecting;
  default:
    return gptut::status::unknown;
  }

}
gptu::item::Connection::Status convert(const gptu::types::status& status) {
  switch (status) {
  case gptut::status::undefined:
    return gptu::item::Connection::Status::PTC_UNDEFINED;
  case gptut::status::connected:
    return gptu::item::Connection::Status::PTC_CONNECTED;
  case gptut::status::connecting:
    return gptu::item::Connection::Status::PTC_CONNECTING;
  case gptut::status::disconnected:
    return gptu::item::Connection::Status::PTC_DISCONNECTED;
  case gptut::status::disconnecting:
    return gptu::item::Connection::Status::PTC_DISCONNECTING;
  default:
    return gptu::item::Connection::Status::PTC_UNKNOWN;
  }
}

} // namespace status
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
