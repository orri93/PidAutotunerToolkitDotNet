#include <map>

#include <QStringList>
#include <QtSerialPort/QSerialPortInfo>

#include <gos/pid/ui/port.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace port {

typedef std::map<QString, int> PortMap;
typedef PortMap::value_type PortValue;
typedef PortMap::iterator PortIterator;
typedef std::map<int, QString> IndexMap;
typedef IndexMap::value_type IndexValue;
typedef IndexMap::iterator IndexIterator;

static PortMap _portmap;
static IndexMap _indexmap;

static QStringList _list;

int index(const QString& value) {
  PortIterator it = _portmap.find(value);
  if (it != _portmap.end()) {
    return it->second;
  }
  return -1;
}

QString value(const int& index) {
  IndexIterator it = _indexmap.find(index);
  if (it != _indexmap.end()) {
    return it->second;
  }
  return QString();
}

QVariant create() {
  int i = 0;
  QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
  for (QSerialPortInfo port : ports) {
    QString porttext = port.portName();
    _portmap.insert(PortValue(porttext, i));
    _indexmap.insert(IndexValue(i, porttext));
    _list.append(porttext);
    i++;
  }
  return QVariant::fromValue(_list);
}

} // namespace tuning
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
