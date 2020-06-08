#include <QStringList>
#include <QDebug>

#include <gos/pid/toolkit/exception.h>
#include <gos/pid/arduino/modbus/master.h>
#include <gos/pid/ui/view/model/tuning.h>
#include <gos/pid/tuning/setting.h>

namespace gp = ::gos::pid;

namespace gpa = ::gos::pid::arduino;

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuvm = ::gos::pid::toolkit::ui::view::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;
namespace gptumt = ::gos::pid::toolkit::ui::model::tuning;
namespace gptumty = ::gos::pid::toolkit::ui::model::types;
namespace gpamtr = ::gos::pid::arduino::modbus::types::registry;
namespace gptt = ::gos::pid::tuning::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace view {
namespace model {

namespace tuning {
static const QString StatusTextArray[] = {
  "Idle",
  "Starting",
  "Tuning",
  "Evaluating",
  "Completed",
  "" };
static const Status::Enum StatusArray[] = {
  Status::Enum::Idle,
  Status::Enum::Starting,
  Status::Enum::Tuning,
  Status::Enum::Evaluating,
  Status::Enum::Completed,
  Status::Enum::Undefined
};
Status::EnumerateModel Status::EnumerateModel_(
  StatusArray,
  StatusTextArray,
  Status::Enum::Undefined,
  Status::StatusRoles::ValueRole,
  Status::StatusRoles::TextRole);
Status::Status(QObject* parent) :
  QAbstractListModel(parent) {
}
int Status::index(const Status::Enum& status) {
  return EnumerateModel_.index(status);
}
Status::Enum Status::status(const int& index) {
  return EnumerateModel_.enumerate(index);
}
int Status::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return EnumerateModel_.count();
}
QVariant Status::data(const QModelIndex& index, int role) const {
  return EnumerateModel_.data(index, role);
}
QHash<int, QByteArray> Status::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[TextRole] = "text";
  roles[ValueRole] = "value";
  return roles;
}
Status::EnumerateModel& Status::enumerateModel() { return EnumerateModel_; }
} // namespace tuning

Tuning::Tuning(
  gptuc::Tuning& tuning,
  gptuvm::Modbus& modbus,
  gptum::Force& forcemodel,
  QObject* parent) :
  gptum::Tuning(parent),
  tuning_(tuning),
  modbus_(modbus),
  forceModel_(forcemodel),
  //method_(gptumt::Method::Enum::None),
  force_(gptum::Force::Enum::Undefined),
  blackBox_(tuning, modbus, forcemodel),
  //isLastMessageError_(false),
  tuningRound_(0),
  isNotifyHandedOver_(false) {
}

Tuning::~Tuning() {
  if (isNotifyHandedOver_) {
    qWarning() << "Notifier has not been recovered - call shutdown";
  }
}

bool Tuning::initialize() {
  QObject::connect(
    &blackBox_,
    &gptuvm::BlackBox::stateChanged,
    this,
    &Tuning::onStateChanged);
  return handoverNotify();
}

bool Tuning::shutdown() {
  return recoverNotify();
}

/* Apply View Model interface implementation */
bool Tuning::apply(gptuc::Interface& configuration) {
  return true;
}
void Tuning::notify() {
}

gptumty::result Tuning::execute(gpamtr::Input& input, const bool& issuccess) {
  switch (method_) {
  case gptum::tuning::Method::Enum::Undefined:
    return gptumty::result::undefined;
  case gptum::tuning::Method::Enum::None:
    return gptumty::result::success;
  case gptum::tuning::Method::Enum::BlackBox:
    return blackBox_.execute(input, issuccess);
  default:
    return gptumty::result::undefined;
  }
}

/* Tuning Notify interface */
void Tuning::notifyForce(const gpa::types::Unsigned& value) {
  int forcenumber = static_cast<int>(value);
  gptum::Force::Enum notifyforce = forceModel_.fromNumber(forcenumber);
  if (force_ != notifyforce) {
    force_ = notifyforce;
    emit forceChanged();
  }
}
void Tuning::notifyKp(const gpa::types::Real& kp) {
  setKp(static_cast<double>(kp));
}
void Tuning::notifyKi(const gpa::types::Real& ki) {
  setKi(static_cast<double>(ki));
}
void Tuning::notifyKd(const gpa::types::Real& kd) {
  setKd(static_cast<double>(kd));
}

  /* Tuning items */
//const gptumt::Method::Enum& Tuning::method() const { return method_; }

  /* Tuning status */
const gptuvm::tuning::Status::Enum Tuning::status() const {
  switch (method_) {
  case gptum::tuning::Method::Enum::Undefined:
  case gptum::tuning::Method::Enum::None:
    return gptuvm::tuning::Status::Enum::Idle;
  case gptum::tuning::Method::Enum::BlackBox:
    switch (blackBox_.state()) {
    case gptuvm::black::box::State::Enum::Undefined:
      return gptuvm::tuning::Status::Enum::Undefined;
    case gptuvm::black::box::State::Enum::Initialize:
      return gptuvm::tuning::Status::Enum::Starting;
    case gptuvm::black::box::State::Enum::Completed:
      return gptuvm::tuning::Status::Enum::Completed;
    case gptuvm::black::box::State::Enum::Reach:
    case gptuvm::black::box::State::Enum::Over:
    case gptuvm::black::box::State::Enum::Under:
    case gptuvm::black::box::State::Enum::Balance:
    case gptuvm::black::box::State::Enum::Cooldown:
      return gptuvm::tuning::Status::Enum::Tuning;
    }
  default:
    return gptuvm::tuning::Status::Enum::Undefined;
  }
}

const bool Tuning::isTuning() const {
  return status() == gptuvm::tuning::Status::Enum::Tuning;
}

/* Tuning items */

/* Controller settings items */
const gptum::Force::Enum& Tuning::force() const { return force_; }

/* Controller tuning items */
//const double& Tuning::kp() const { return triplet_.kp(); }
//const double& Tuning::ki() const { return triplet_.ki(); }
//const double& Tuning::kd() const { return triplet_.kd(); }

gptuvm::BlackBox* Tuning::blackBox() { return &blackBox_; }
gptuvm::BlackBox& Tuning::getBlackBox() { return blackBox_; }

void Tuning::setMethod(const gptum::tuning::Method::Enum& method) {
  gptuvm::tuning::Status::Enum last = status();
  if (applyMethod(method)) {
    emit methodChanged();
    if (status() != last) {
      emit statusChanged();
    }
  }
}

void Tuning::onStateChanged() {
  switch (method_) {
  case gptum::tuning::Method::Enum::Undefined:
  case gptum::tuning::Method::Enum::None:
    /* Do nothing */;
  case gptum::tuning::Method::Enum::BlackBox:
    emit statusChanged();
    break;
  default:
    /* Do nothing */;
  }
}

/* Controller settings items */
void Tuning::setForce(const gptum::Force::Enum& force) {
  if (force_ != force) {
    force_ = force;
    emit forceChanged();
  }
}
//
//void Tuning::setKp(const double& value) {
//  if (triplet_.kp() != value) {
//    triplet_.setKp(value);
//    emit kpChanged();
//  }
//}
//void Tuning::setKi(const double& value) {
//  if (triplet_.ki() != value) {
//    triplet_.setKi(value);
//    emit kiChanged();
//  }
//}
//void Tuning::setKd(const double& value) {
//  if (triplet_.kd() != value) {
//    triplet_.setKd(value);
//    emit kdChanged();
//  }
//}


bool Tuning::handoverNotify() {
  if (!isNotifyHandedOver_) {
    gp::tuning::NotifyPointer notify(this);
    if (notify) {
      isNotifyHandedOver_ = gp::tuning::black::box::notify::handover(notify);
      if (isNotifyHandedOver_) {
        return true;
      } else {
        setLastError("Failed to hand over notify");
      }
    } else {
      setLastError("Failed to create notify for hand over");
    }
  } else {
    setLastError("Notify has already been handed over");
  }
  return false;
}

bool Tuning::recoverNotify() {
  if (isNotifyHandedOver_) {
    gp::tuning::NotifyPointer notify;
    isNotifyHandedOver_ = !(gp::tuning::black::box::notify::recover(notify));
    if (!isNotifyHandedOver_) {
      gp::tuning::Nofity* pointer = notify.release();
      return true;
    } else {
      setLastError("Failed to recover notify");
    }
  } else {
    setLastError("Notify has not yet been handed over");
  }
  return false;
}


} // namespace model
} // namespace view
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

