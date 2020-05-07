#ifndef GOS_PID_TUNING_UI_LIB_STATUS_H_
#define GOS_PID_TUNING_UI_LIB_STATUS_H_

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/connection.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace status {

::gos::pid::toolkit::ui::types::status convert(
  const ::gos::pid::toolkit::ui::item::Connection::Status& status);
::gos::pid::toolkit::ui::item::Connection::Status convert(
  const ::gos::pid::toolkit::ui::types::status& status);

} // namespace status
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
