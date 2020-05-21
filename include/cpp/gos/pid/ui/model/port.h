#ifndef GOS_PID_TUNING_UI_MODEL_PORT_H_
#define GOS_PID_TUNING_UI_MODEL_PORT_H_

#include <QVariant>

#define GOS_QML_MODEL_PORT "portModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace port {

int index(const QString& value);

QString value(const int& index);

QVariant create();

} // namespace port
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
