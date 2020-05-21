#include <gos/pid/ui/model/status.h>

#define GOS_QML_MODEL_STATUS_COUNT 5

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

static const QString StatusTextArray[GOS_QML_MODEL_STATUS_COUNT + 1] = {
  "Connecting",
  "Connected",
  "Disconnecting",
  "Disconnected",
  "Unknown",
  "" };

static Status::Enum StatusEnumArray[GOS_QML_MODEL_STATUS_COUNT + 1] = {
  Status::Enum::Connecting,
  Status::Enum::Connected,
  Status::Enum::Disconnecting,
  Status::Enum::Disconnected,
  Status::Enum::Unknown,
  Status::Enum::Undefined
};

Status::EnumerateModel Status::EnumerateModel_(
  StatusEnumArray,
  StatusTextArray,
  Status::Enum::Undefined,
  Status::StatusRoles::ValueRole,
  Status::StatusRoles::TextRole);

Status::Status(QObject* parent) :
  QAbstractListModel(parent) {
}

int Status::index(const Status::Enum& status) {
  int index = EnumerateModel_.index(status);
  return index;
}

Status::Enum Status::status(const int& index) {
  
  Status::Enum status = EnumerateModel_.enumerate(index);
  return status;
}

int Status::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return EnumerateModel_.count();
}

QVariant Status::data(const QModelIndex& index, int role) const {
  return EnumerateModel_.data(index, role);
}

//![0]
QHash<int, QByteArray> Status::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[TextRole] = "text";
  roles[ValueRole] = "value";
  return roles;
}

Status::EnumerateModel& Status::enumerateModel() {
  return EnumerateModel_;
}


} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
