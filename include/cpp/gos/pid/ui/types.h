#ifndef GOS_PID_TUNING_UI_TYPES_H_
#define GOS_PID_TUNING_UI_TYPES_H_

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace types {

enum class status {
  undefined,
  idle,
  connecting,
  connected,
  disconnecting,
  down
};

} // namespace types
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
