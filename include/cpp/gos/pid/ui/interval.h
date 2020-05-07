#ifndef GOS_PID_TUNING_UI_LIB_MODEL_INTERVAL_H_
#define GOS_PID_TUNING_UI_LIB_MODEL_INTERVAL_H_

#include <QVariant>

#define GOS_QML_MODEL_INTERVAL "intervalModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace interval {

int index(const int& value);
int value(const int& index);

QVariant create();

} // namespace interval
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
