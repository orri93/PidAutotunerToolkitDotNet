#ifndef GOS_PID_TUNING_UI_MODEL_TYPES_H_
#define GOS_PID_TUNING_UI_MODEL_TYPES_H_

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace types {

enum class result {
  undefined,
  success,
  warning,
  error,
  fatal
};

} // namespace types
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
