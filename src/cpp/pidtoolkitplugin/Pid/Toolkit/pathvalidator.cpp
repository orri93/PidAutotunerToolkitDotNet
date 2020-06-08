#include <QFileInfo>
#include <QFile>
#include <QDir>

#include <gos/pid/ui/plugin/pathvalidator.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace validator {

Path::Path(QObject* parent) :
  QValidator(parent),
  type_(Type::PATH_VALIDATOR_TYPE_ANY) {
}

QValidator::State Path::validate(QString& input, int& pos) const {
  Q_UNUSED(pos)
  if (input.isEmpty()) {
    return Acceptable;
  }
  QFileInfo fileinfo(input);
  QDir directory(input);
  QString pathonly = fileinfo.path();
  QString filenameonly = fileinfo.baseName();
  switch (type_) {
  case Type::PATH_VALIDATOR_TYPE_ANY:
    switch (restriction_) {
    case PATH_VALIDATOR_RESTRICTION_NONE:
      return Acceptable;
    case PATH_VALIDATOR_RESTRICTION_EXISTS:
      return (fileinfo.exists() || directory.exists()) ? Acceptable : Invalid;
    case PATH_VALIDATOR_RESTRICTION_NOT_EXISTS:
      return (fileinfo.exists() || directory.exists()) ? Invalid : Acceptable;
    case PATH_VALIDATOR_RESTRICTION_ABSOLUTE:
      return (QDir::isAbsolutePath(pathonly) || QDir::isAbsolutePath(input)) ?
        Acceptable : Invalid;
    case PATH_VALIDATOR_RESTRICTION_EXISTS_ABSOLUTE:
      return (fileinfo.exists() || directory.exists()) ?
        ((QDir::isAbsolutePath(pathonly) || QDir::isAbsolutePath(input)) ?
          Acceptable : Invalid ): Invalid;
    case PATH_VALIDATOR_RESTRICTION_NOT_EXISTS_ABSOLUTE:
      return (fileinfo.exists() || directory.exists()) ? Invalid :
        ((QDir::isAbsolutePath(pathonly) || QDir::isAbsolutePath(input)) ?
          Acceptable : Invalid);
    default:
      return Invalid;
    }
  case Type::PATH_VALIDATOR_TYPE_DIRECTORY:
    if (fileinfo.exists()) {
      return Invalid;
    } else {
      switch (restriction_) {
      case PATH_VALIDATOR_RESTRICTION_NONE:
        return Acceptable;
      case PATH_VALIDATOR_RESTRICTION_EXISTS:
        return (directory.exists()) ? Acceptable : Invalid;
      case PATH_VALIDATOR_RESTRICTION_NOT_EXISTS:
        return (directory.exists()) ? Invalid : Acceptable;
      case PATH_VALIDATOR_RESTRICTION_ABSOLUTE:
        return (QDir::isAbsolutePath(input)) ? Acceptable : Invalid;
      case PATH_VALIDATOR_RESTRICTION_EXISTS_ABSOLUTE:
        return (directory.exists()) ? ((QDir::isAbsolutePath(input)) ?
            Acceptable : Invalid) : Invalid;
      case PATH_VALIDATOR_RESTRICTION_NOT_EXISTS_ABSOLUTE:
        return (directory.exists()) ? Invalid : ((QDir::isAbsolutePath(input)) ?
          Acceptable : Invalid);
      default:
        return Invalid;
      }
    }
  case Type::PATH_VALIDATOR_TYPE_FILE:
    switch (restriction_) {
    case PATH_VALIDATOR_RESTRICTION_NONE:
      return Acceptable;
    case PATH_VALIDATOR_RESTRICTION_EXISTS:
      return (fileinfo.exists()) ? Acceptable : Invalid;
    case PATH_VALIDATOR_RESTRICTION_NOT_EXISTS:
      return (fileinfo.exists()) ? Invalid : Acceptable;
    case PATH_VALIDATOR_RESTRICTION_ABSOLUTE:
      if (pathonly.compare(".") != 0) {
#ifdef _WIN32
        if (pathonly.length() == 2) {
          QChar second = pathonly.at(1);
          if (second.toLatin1() == ':') {
            return Invalid;
          }
        }
#endif
        QDir pathonlydir(pathonly);
        return (pathonlydir.exists() && QDir::isAbsolutePath(pathonly))
          ? Acceptable : Invalid;
      } else  {
        return Invalid;
      }
    case PATH_VALIDATOR_RESTRICTION_EXISTS_ABSOLUTE:
      return (fileinfo.exists()) ? ((QDir::isAbsolutePath(pathonly)) ?
        Acceptable : Invalid) : Invalid;
    case PATH_VALIDATOR_RESTRICTION_NOT_EXISTS_ABSOLUTE:
      return (fileinfo.exists()) ? Invalid : ((QDir::isAbsolutePath(pathonly)) ?
        Acceptable : Invalid);
    default:
      return Invalid;
    }
    return QFile::exists(input) ? Acceptable : Invalid;
  default:
    return Invalid;
  }
}

const Path::Type& Path::type() const {
  return type_;
}

const int Path::typeNumber() const {
  return static_cast<int>(type_);
}

const Path::Restriction& Path::restriction() const {
  return restriction_;
}

const int Path::restrictionNumber() const {
  return static_cast<int>(restriction_);
}

void Path::setType(const Type& type) {
  type_ = type;
}

void Path::setTypeNumber(const int& number) {
  setType(static_cast<Type>(number));
}

void Path::setRestriction(const Restriction& restriction) {
  restriction_ = restriction;
}

void Path::setRestrictionNumber(const int& number) {
  setRestriction(static_cast<Restriction>(number));
}

} // namespace validator
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
