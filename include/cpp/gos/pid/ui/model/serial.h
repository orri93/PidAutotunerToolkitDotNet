#ifndef GOS_PID_TUNING_UI_MODEL_SERIAL_H_
#define GOS_PID_TUNING_UI_MODEL_SERIAL_H_

#include <QObject>
#include <QtGlobal>
#include <QAbstractListModel>

#include <gos/pid/ui/model/value.h>

#define GOS_QML_MODEL_SERIAL "serialModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

class Serial : public QAbstractListModel {
  Q_OBJECT
public:
  enum SerialRoles {
    PortValueRole = Qt::UserRole + 1,
    PortTextRole,
    BaudValueRole,
    BaudTextRole
  };
  typedef ::gos::pid::toolkit::ui::model::Value<QString, SerialRoles> PortModel;
  typedef ::gos::pid::toolkit::ui::model::Value<int, SerialRoles> BaudModel;
  Q_ENUM(SerialRoles)

  Serial(const SerialRoles& type, QObject* parent = nullptr);

  Q_INVOKABLE bool create(const SerialRoles& type = PortValueRole);
  Q_INVOKABLE int index(const QString& port);
  Q_INVOKABLE int index(const int& baud);
  Q_INVOKABLE QString port(const int& index);
  Q_INVOKABLE int baud(const int& index);

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  PortModel& portModel();

  static BaudModel& baudModel();

protected:
  QHash<int, QByteArray> roleNames() const;
private:
  SerialRoles type_;
  PortModel portModel_;
  static BaudModel BaudModel_;
};

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
