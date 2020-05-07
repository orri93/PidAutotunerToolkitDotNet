#ifndef GOS_PID_TUNING_UI_LIB_MODEL_MODE_H_
#define GOS_PID_TUNING_UI_LIB_MODEL_MODE_H_

#include <QVariant>

#define GOS_QML_MODEL_MODE "modeModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace mode {

int index(const int& mode);

int mode(const int& index);

QVariant create();

} // namespace mode
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
