#include <QFile>
#include <QDir>

#include <gos/pid/ui/pathvalidator.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace validator {

Path::Path(QObject* parent) :
  QValidator(parent),
  type_(Type::PATH_VALIDATOR_ANY) {
}

QValidator::State Path::validate(QString& input, int& pos) const {
  Q_UNUSED(pos)
  if (input.isEmpty()) {
    return Acceptable;
  }
  switch (type_) {
  case Type::PATH_VALIDATOR_ANY:
    return (QFile::exists(input) || QDir::isAbsolutePath(input)) ?
      Acceptable : Invalid;
  case Type::PATH_VALIDATOR_DIRECTORY:
    return QDir::isAbsolutePath(input) ? Acceptable : Invalid;
  case Type::PATH_VALIDATOR_FILE:
    return QFile::exists(input) ? Acceptable : Invalid;
  }
  return Invalid;
}

const Path::Type& Path::type() const {
  return type_;
}

void Path::setType(const Type& type) {
  type_ = type;
}

} // namespace validator
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
