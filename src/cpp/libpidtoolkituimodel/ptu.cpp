#include <gos/pid/ui/model/ptu.h>
//#include <gos/pid/ui/configuration/interface.h>

#define GOS_QML_STATUS_COUNT 4

namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gptum = ::gos::pid::toolkit::ui::model;

//namespace pgtuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

namespace ptu {
static const QString StatusTextArray[GOS_QML_STATUS_COUNT + 1] = {
  "Startup",
  "Initializing",
  "Writing",
  "Idle",
  "" };

static Status::Enum StatusEnumArray[GOS_QML_STATUS_COUNT + 1] = {
  Status::Enum::Startup,
  Status::Enum::Initializing,
  Status::Enum::Writing,
  Status::Enum::Idle,
  Status::Enum::Undefined
};

Status::EnumerateModel Status::EnumerateModel_(
  StatusEnumArray,
  StatusTextArray,
  Status::Enum::Undefined,
  Status::PtuStatusRoles::ValueRole,
  Status::PtuStatusRoles::TextRole);

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

Status::EnumerateModel& Status::enumerateModel() {
  return EnumerateModel_;
}
}

Ptu::Ptu(QObject* parent) :
  QObject(parent),
  ptStatus_(gptum::ptu::Status::Enum::Undefined),
  isLastMessageError_(false) {
}

Ptu::~Ptu() {
}

bool Ptu::initialize() {
  return true;
}

QSettings* Ptu::read(QSettings* settings) {
  return nullptr;
}

QSettings* Ptu::write(QSettings* settings) {
  return nullptr;
}

const gptum::ptu::Status::Enum& Ptu::ptStatus() const { return ptStatus_; }
const bool Ptu::ptReady() const {
  switch (ptStatus_) {
  case gos::pid::toolkit::ui::model::ptu::Status::Enum::Undefined:
  case gos::pid::toolkit::ui::model::ptu::Status::Enum::Startup:
  case gos::pid::toolkit::ui::model::ptu::Status::Enum::Initializing:
  case gos::pid::toolkit::ui::model::ptu::Status::Enum::Writing:
    return false;
  case gos::pid::toolkit::ui::model::ptu::Status::Enum::Idle:
    return true;
  default:
    return false;
  }
}

const QString& Ptu::lastMessage() const { return lastMessage_; }
const bool& Ptu::isLastMessageError() const { return isLastMessageError_; }

/* Messages helpers */
void Ptu::setLastMessage(const QString& message, const bool isLastMessageError) {
  isLastMessageError_ = isLastMessageError;
  if (lastMessage_ != message) {
    lastMessage_ = message;
    emit lastMessageChanged();
  }
}
void Ptu::setLastError(const QString& message) {
  setLastMessage(message, true);
}


/* Status helpers */
void Ptu::startup() { setPtStatus(gptum::ptu::Status::Enum::Startup); }
void Ptu::initializing() { setPtStatus(gptum::ptu::Status::Enum::Initializing); }
void Ptu::writing() { setPtStatus(gptum::ptu::Status::Enum::Writing); }
void Ptu::idle() { setPtStatus(gptum::ptu::Status::Enum::Idle); }

bool Ptu::applyPtStatus(const gptum::ptu::Status::Enum& status) {
  if (ptStatus_ != status) {
    ptStatus_ = status;
    return true;
  } else {
    return false;
  }
}

void Ptu::setPtStatus(const gptum::ptu::Status::Enum& status) {
  if (applyPtStatus(status)) {
    emit ptStatusChanged();
  }
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
