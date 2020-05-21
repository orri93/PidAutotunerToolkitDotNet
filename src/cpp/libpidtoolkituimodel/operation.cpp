#include <QQmlEngine>
#include <QDebug>

#include <gos/pid/ui/model/operation.h>

#define GOS_QML_OPERATION_COUNT 2

namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

static const QString OperationTextArray[GOS_QML_OPERATION_COUNT + 1] = {
  "Add",
  "Subtract"
  "" };

static Operation::Enum OperationEnumArray[GOS_QML_OPERATION_COUNT + 1] = {
  Operation::Enum::Add,
  Operation::Enum::Subtract,
  Operation::Enum::Undefined
};

Operation::EnumerateModel Operation::EnumerateModel_(
  OperationEnumArray,
  OperationTextArray,
  Operation::Enum::Undefined,
  Operation::OperationRoles::ValueRole,
  Operation::OperationRoles::TextRole);

Operation::Operation(QObject* parent) :
  QAbstractListModel(parent) {
}

int Operation::index(const Operation::Enum& operation) {
  return EnumerateModel_.index(operation);
}

Operation::Enum Operation::operation(const int& index) {
  return EnumerateModel_.enumerate(index);
}

int Operation::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return EnumerateModel_.count();
}

QVariant Operation::data(const QModelIndex& index, int role) const {
  return EnumerateModel_.data(index, role);
}

QHash<int, QByteArray> Operation::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[TextRole] = "text";
  roles[ValueRole] = "value";
  return roles;
}

Operation::EnumerateModel& Operation::enumerateModel() {
  return EnumerateModel_;
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

