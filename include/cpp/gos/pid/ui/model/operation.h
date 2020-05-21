#ifndef GOS_PID_TUNING_UI_MODEL_OPERATION_H_
#define GOS_PID_TUNING_UI_MODEL_OPERATION_H_

#include <QObject>
#include <QtGlobal>
#include <QAbstractListModel>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/enumerate.h>

#define GOS_QML_MODEL_OPERATION "operationModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

class Operation : public QAbstractListModel {
  Q_OBJECT
public:
  enum class Enum : quint8 {
    Undefined,
    Add,
    Subtract
  };
  enum OperationRoles {
    TextRole = Qt::UserRole + 1,
    ValueRole
  };
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, OperationRoles> EnumerateModel;
  Q_ENUM(Enum)
  Q_ENUM(OperationRoles)

  Operation(QObject* parent = nullptr);

  Q_INVOKABLE int index(const Enum& operation);
  Q_INVOKABLE Enum operation(const int& index);

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  static EnumerateModel& enumerateModel();

protected:
  QHash<int, QByteArray> roleNames() const;
private:

  static EnumerateModel EnumerateModel_;
};

namespace to {
QString string(const ::gos::pid::toolkit::ui::types::operation& operation);
}

::gos::pid::toolkit::ui::types::operation parse(const QString& text);

int index(const ::gos::pid::toolkit::ui::types::operation& moperationode);

::gos::pid::toolkit::ui::types::operation operation(const int& index);

QVariant create();

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
