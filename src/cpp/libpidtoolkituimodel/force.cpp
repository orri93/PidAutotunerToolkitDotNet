#include <QQmlEngine>
#include <QDebug>

#include <gos/pid/arduino/modbus/master.h>

#include <gos/pid/ui/model/force.h>

#define GOS_QML_FORCE_COUNT 4

namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

static const int ForceNumberArray[GOS_QML_FORCE_COUNT + 1] = {
  GOT_PI_FORCE_OFF,
  GOT_PI_FORCE_IDLE,
  GOT_PI_FORCE_MANUAL,
  GOT_PI_FORCE_AUTO,
  -1
};
static const QString ForceTextArray[GOS_QML_FORCE_COUNT + 1] = {
  "Off",
  "Idle",
  "Manual",
  "Automatic",
  ""
};
static Force::Enum ForceEnumArray[GOS_QML_FORCE_COUNT + 1] = {
  Force::Enum::Off,
  Force::Enum::Idle,
  Force::Enum::Manual,
  Force::Enum::Auto,
  Force::Enum::Undefined
};

Force::EnumerateModel Force::EnumerateModel_(
  ForceEnumArray,
  ForceTextArray,
  Force::Enum::Undefined,
  Force::ForceRoles::ValueRole,
  Force::ForceRoles::TextRole);

Force::NumberModel Force::NumberModel_(
  ForceEnumArray,
  ForceNumberArray,
  -1,
  Force::Enum::Undefined,
  Force::ForceRoles::ValueRole,
  Force::ForceRoles::NumberRole);

Force::Force(QObject* parent) :
  QAbstractListModel(parent) {
}

int Force::index(const Force::Enum& force) {
  return EnumerateModel_.index(force);
}
Force::Enum Force::force(const int& index) {
  return EnumerateModel_.enumerate(index);
}
int Force::number(const Force::Enum& force) {
  return NumberModel_.toValue(force);
}
int Force::number(const int& index) {
  return NumberModel_.valueFromIndex(index);
}
Force::Enum Force::fromNumber(const int& number) {
  return NumberModel_.fromValue(number);
}

int Force::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return EnumerateModel_.count();
}

QVariant Force::data(const QModelIndex& index, int role) const {
  switch (role) {
  case ForceRoles::TextRole:
  case ForceRoles::ValueRole:
    return EnumerateModel_.data(index, role);
  case ForceRoles::NumberRole:
    return NumberModel_.data(index, role);
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> Force::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[TextRole] = "text";
  roles[ValueRole] = "value";
  roles[NumberRole] = "number";
  return roles;
}

Force::EnumerateModel& Force::enumerateModel() {
  return EnumerateModel_;
}

Force::NumberModel& Force::numberModel() {
  return NumberModel_;
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

