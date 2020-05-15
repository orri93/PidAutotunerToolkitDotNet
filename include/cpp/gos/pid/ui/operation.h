#ifndef GOS_PID_TUNING_UI_LIB_MODEL_OPERATION_H_
#define GOS_PID_TUNING_UI_LIB_MODEL_OPERATION_H_

#include <QVariant>
#include <QString>

#include <gos/pid/ui/types.h>

#define GOS_QML_MODEL_OPERATION "operationModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace operation {

namespace to {
QString string(const ::gos::pid::toolkit::ui::types::operation& operation);
}

::gos::pid::toolkit::ui::types::operation parse(const QString& text);

int index(const ::gos::pid::toolkit::ui::types::operation& moperationode);

::gos::pid::toolkit::ui::types::operation operation(const int& index);

QVariant create();

} // namespace operation
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
