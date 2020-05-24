#ifndef GOS_PID_TUNING_UI_MODEL_FORCE_H_
#define GOS_PID_TUNING_UI_MODEL_FORCE_H_

#include <QObject>
#include <QtGlobal>
#include <QAbstractListModel>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/enumerate.h>

#define GOS_QML_MODEL_FORCE "forceModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

class Force : public QAbstractListModel {
  Q_OBJECT
public:
  enum class Enum : quint8 {
    Undefined,
    Off,
    Idle,
    Manual,
    Auto
  };
  enum ForceRoles {
    TextRole = Qt::UserRole + 1,
    ValueRole,
    NumberRole
  };
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, ForceRoles> EnumerateModel;
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, ForceRoles, int> NumberModel;
  Q_ENUM(Enum)
  Q_ENUM(ForceRoles)

  Force(QObject* parent = nullptr);

  Q_INVOKABLE int index(const Enum& force);
  Q_INVOKABLE Enum force(const int& index);
  Q_INVOKABLE int number(const Enum& force);
  Q_INVOKABLE int number(const int& index);
  Q_INVOKABLE Enum fromNumber(const int& number);

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  static EnumerateModel& enumerateModel();
  static NumberModel& numberModel();

protected:
  QHash<int, QByteArray> roleNames() const;
private:

  static EnumerateModel EnumerateModel_;
  static NumberModel NumberModel_;
};

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
