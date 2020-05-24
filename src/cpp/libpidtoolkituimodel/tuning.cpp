#include <QStringList>

#include <gos/pid/arduino/modbus/master.h>
#include <gos/pid/ui/model/tuning.h>
#include <gos/pid/tuning/setting.h>

namespace gp = ::gos::pid;

namespace gpa = ::gos::pid::arduino;

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;
namespace gptumt = ::gos::pid::toolkit::ui::model::tuning;
namespace gptumty = ::gos::pid::toolkit::ui::model::types;
namespace gpamtr = ::gos::pid::arduino::modbus::types::registry;
namespace gptt = ::gos::pid::tuning::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

namespace tuning {
static const QString MethodTextArray[] = { "None", "Black Box", "" };
static const Method::Enum MethodArray[] = {
  Method::Enum::None,
  Method::Enum::BlackBox,
  Method::Enum::Undefined
};
Method::EnumerateModel Method::EnumerateModel_(
  MethodArray,
  MethodTextArray,
  Method::Enum::Undefined,
  Method::MethodRoles::ValueRole,
  Method::MethodRoles::TextRole);
Method::Method(QObject* parent) :
  QAbstractListModel(parent) {
}
int Method::index(const Method::Enum& method) {
  return EnumerateModel_.index(method);
}

Method::Enum Method::method(const int& index) {
  return EnumerateModel_.enumerate(index);
}
int Method::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return EnumerateModel_.count();
}
QVariant Method::data(const QModelIndex& index, int role) const {
  return EnumerateModel_.data(index, role);
}
QHash<int, QByteArray> Method::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[TextRole] = "text";
  roles[ValueRole] = "value";
  return roles;
}
Method::EnumerateModel& Method::enumerateModel() { return EnumerateModel_; }
} // namespace tuning

Tuning::Tuning(QObject* parent) :
  Ptu(parent),
  method_(gptumt::Method::Enum::None) {
}

Tuning::Tuning(const Tuning& tuning) :
  method_(tuning.method_) {
}

Tuning& Tuning::set(const Tuning& tuning) {
  if (this != &tuning) {
    setMethod(tuning.method_);
    setKp(tuning.kp());
    setKi(tuning.ki());
    setKd(tuning.kd());
  }
  return *this;
}

/* Tuning items */
const gptum::tuning::Method::Enum& Tuning::method() const { return method_; }

/* Controller tuning items */
const double& Tuning::kp() const { return triplet_.kp(); }
const double& Tuning::ki() const { return triplet_.ki(); }
const double& Tuning::kd() const { return triplet_.kd(); }

bool Tuning::applyMethod(const gptum::tuning::Method::Enum& method) {
  if (method_ != method) {
    method_ = method;
    return true;
  } else {
    return false;
  }
}

bool Tuning::applyKp(const double& value) {
  if (triplet_.kp() != value) {
    triplet_.setKp(value);
    return true;
  } else {
    return false;
  }
}
bool Tuning::applyKi(const double& value) {
  if (triplet_.ki() != value) {
    triplet_.setKi(value);
    return true;
  } else {
    return false;
  }
}
bool Tuning::applyKd(const double& value) {
  if (triplet_.kd() != value) {
    triplet_.setKd(value);
    return true;
  } else {
    return false;
  }
}

void Tuning::setMethod(const gptum::tuning::Method::Enum& method) {
  if (applyMethod(method)) {
    emit methodChanged();
  }
}

void Tuning::setKp(const double& value) {
  if (applyKp(value)) {
    emit kpChanged();
  }
}
void Tuning::setKi(const double& value) {
  if (applyKi(value)) {
    emit kiChanged();
  }
}
void Tuning::setKd(const double& value) {
  if (applyKd(value)) {
    emit kdChanged();
  }
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

