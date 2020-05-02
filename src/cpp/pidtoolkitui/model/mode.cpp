#include <QStringList>

#include <model/mode.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace mode {

static const QString Modes[] = { "Idle", "Manual", "Automatic", "" };

static QStringList _list;

int index(const int& mode) {
  return mode - 1;
}

int mode(const int& index) {
  return index + 1;
}

QVariant create() {
  const QString* mode = Modes;
  while (*mode != "") {
    _list.append(*mode);
    mode++;
  }
  return QVariant::fromValue(_list);
}

} // namespace mode
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

