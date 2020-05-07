#ifndef GOS_PID_TUNING_UI_LIB_MODEL_BAUD_H_
#define GOS_PID_TUNING_UI_LIB_MODEL_BAUD_H_

#include <QVariant>

#define GOS_QML_MODEL_BAUD "baudModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace baud {

int index(const int value);

int value(const int& index);

QVariant create();

} // namespace baud
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
