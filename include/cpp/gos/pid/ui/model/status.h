#ifndef GOS_PID_TUNING_UI_MODEL_STATUS_H_
#define GOS_PID_TUNING_UI_MODEL_STATUS_H_

#include <QObject>
#include <QtGlobal>
#include <QAbstractListModel>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/enumerate.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

class Status : public QAbstractListModel {
  Q_OBJECT
public:
  enum class Enum : quint8 {
    Undefined,
    Connecting,
    Connected,
    Disconnecting,
    Disconnected,
    Unknown
  };
  enum StatusRoles {
    TextRole = Qt::UserRole + 1,
    ValueRole
  };
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, StatusRoles> EnumerateModel;
  Q_ENUM(Enum)
  Q_ENUM(StatusRoles)

  Status(QObject* parent = nullptr);

  Q_INVOKABLE int index(const Enum& status);
  Q_INVOKABLE Enum status(const int& index);

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  static EnumerateModel& enumerateModel();

protected:
  QHash<int, QByteArray> roleNames() const;
private:

  static EnumerateModel EnumerateModel_;
};


} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
