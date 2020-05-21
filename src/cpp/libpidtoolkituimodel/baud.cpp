#include <map>

#include <QStringList>

#include <gos/pid/ui/model/baud.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace baud {

typedef std::map<int, int> BaudMap;
typedef BaudMap::value_type BaudValue;
typedef BaudMap::iterator BaudIterator;

static QStringList _list;

static const int Bauds[] = {
  256000, 128000, 115200, 57600, 38400, 19200, 14400,
  9600, 4800,  2400, 1200, 600, 300, 110, 0
};

static BaudMap _baudmap;
static BaudMap _indexmap;

int index(const int value) {
  BaudIterator it = _baudmap.find(value);
  if (it != _baudmap.end()) {
    return it->second;
  }
  return -1;
}

int value(const int& index) {
  BaudIterator it = _indexmap.find(index);
  if (it != _indexmap.end()) {
    return it->second;
  }
  return -1;
}

QVariant create() {
  int i = 0;
  const int* baud = Bauds;
  while (*baud != 0) {
    _list.append(QString("%1 bps").arg(*baud));
    _baudmap.insert(BaudValue(*baud, i));
    _indexmap.insert(BaudValue(i, *baud));
    baud++;
    i++;
  }
  return QVariant::fromValue(_list);
}

} // namespace baud
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
