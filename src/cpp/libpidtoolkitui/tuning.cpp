#include <QStringList>

#include <gos/pid/ui/tuning.h>

namespace gptt = ::gos::pid::tuning::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace tuning {

static const QString Tunings[] = { "None", "Black Box", "" };

static QStringList _list;

int index(const gptt::TuningMode& mode) {
  switch (mode) {
  case gptt::TuningMode::undefined:
    return 0;
  case gptt::TuningMode::blackbox:
    return 1;
  default:
    return -1;
  }
}

gptt::TuningMode value(const int& index) {
  switch (index) {
  case 0:
    return gptt::TuningMode::undefined;
  case 1:
    return gptt::TuningMode::blackbox;
  default:
    return gptt::TuningMode::undefined;
  }
}

QVariant create() {
  const QString* tuning = Tunings;
  while (*tuning != "") {
    _list.append(*tuning);
    tuning++;
  }
  return QVariant::fromValue(_list);
}

} // namespace tuning
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

