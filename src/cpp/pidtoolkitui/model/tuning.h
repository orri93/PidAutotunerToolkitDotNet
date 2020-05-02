#ifndef GOS_PID_TUNING_UI_MODEL_TUNING_H_
#define GOS_PID_TUNING_UI_MODEL_TUNING_H_

#include <QVariant>

#include <gos/pid/tuning/types.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace tuning {

int index(const ::gos::pid::tuning::types::TuningMode& mode);

::gos::pid::tuning::types::TuningMode value(const int& index);

QVariant create();

} // namespace tuning
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
