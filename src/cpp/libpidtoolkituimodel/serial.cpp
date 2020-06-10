#include <map>

#include <QStringList>
#include <QtSerialPort/QSerialPortInfo>

#include <gos/pid/ui/model/serial.h>

namespace gptum = ::gos::pid::toolkit::ui::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

namespace baud {
static const int BaudArray[] = {
  256000, 128000, 115200, 57600, 38400, 19200, 14400,
  9600, 4800,  2400, 1200, 600, 300, 110, -1
};
} // namespace baud

Serial::BaudModel Serial::BaudModel_(
  gptum::baud::BaudArray,
  -1,
  Serial::SerialRoles::BaudValueRole,
  Serial::SerialRoles::BaudTextRole);

Serial::Serial(const SerialRoles& type, QObject* parent) :
  QAbstractListModel(parent),
  type_(type),
  portModel_(QString(), PortValueRole, PortTextRole) {
}

bool Serial::create(const SerialRoles& type) {
  portModel_.clear();
  QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
  for (QSerialPortInfo port : ports) {
    QString porttext = port.portName();
    portModel_.add(porttext);
  }
  return true;
}
int Serial::index(const QString& port) {
  return portModel_.index(port);
}
int Serial::index(const int& baud) {
  return BaudModel_.index(baud);
}
QString Serial::port(const int& index) {
  return portModel_.value(index);
}
int Serial::baud(const int& index) {
  return BaudModel_.value(index);
}

int Serial::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  switch (type_) {
  case PortValueRole:
  case PortTextRole:
    return portModel_.count();
  case BaudValueRole:
  case BaudTextRole:
    return BaudModel_.count();
  }
  return 0;
}

QVariant Serial::data(const QModelIndex& index, int role) const {
  switch (type_) {
  case PortValueRole:
  case PortTextRole:
    return portModel_.data(index, role);
  case BaudValueRole:
  case BaudTextRole:
    return BaudModel_.data(index, role);
  }
  return QVariant();
}

QHash<int, QByteArray> Serial::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[PortTextRole] = "portText";
  roles[PortValueRole] = "portValue";
  roles[BaudTextRole] = "baudText";
  roles[BaudValueRole] = "baudValue";
  return roles;
}

Serial::PortModel& Serial::portModel() {
  return portModel_;
}

Serial::BaudModel& Serial::baudModel(){
  return BaudModel_;
}


} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
