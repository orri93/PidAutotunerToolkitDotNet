#ifndef GOS_PID_TUNING_UI_PATH_VALIDATOR_H_
#define GOS_PID_TUNING_UI_PATH_VALIDATOR_H_

#include <QValidator>

#define GOS_QML_VALIDATOR_NAME_PATH "PathValidator"
#define GOS_QML_VALIDATOR_URI_PATH GOS_QML_VALIDATOR_NAME_PATH

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace validator {

class Path : public QValidator {
  Q_OBJECT
  Q_PROPERTY(Type type READ type WRITE setType)
  Q_PROPERTY(Restriction restriction READ restriction WRITE setRestriction)
  Q_PROPERTY(int typeNumber READ typeNumber WRITE setTypeNumber)
  Q_PROPERTY(int restrictionNumber READ restrictionNumber WRITE setRestrictionNumber)
public:

  enum Type {
    PATH_VALIDATOR_TYPE_ANY = 0x00,
    PATH_VALIDATOR_TYPE_DIRECTORY = 0x01,
    PATH_VALIDATOR_TYPE_FILE = 0x02
  };
  Q_ENUMS(Type)

  enum Restriction {
    PATH_VALIDATOR_RESTRICTION_NONE = 0x00,
    PATH_VALIDATOR_RESTRICTION_EXISTS = 0x01,
    PATH_VALIDATOR_RESTRICTION_NOT_EXISTS = 0x02,
    PATH_VALIDATOR_RESTRICTION_ABSOLUTE = 0x04,
    PATH_VALIDATOR_RESTRICTION_EXISTS_ABSOLUTE = 0x05,
    PATH_VALIDATOR_RESTRICTION_NOT_EXISTS_ABSOLUTE = 0x06
  };

  Q_ENUMS(Restriction)

  explicit Path(QObject* parent = nullptr);
  virtual State validate(QString& input, int& pos) const;

  const Type& type() const;
  const int typeNumber() const;
  const Restriction& restriction() const;
  const int restrictionNumber() const;

  void setType(const Type& type);
  void setTypeNumber(const int& number);
  void setRestriction(const Restriction& restriction);
  void setRestrictionNumber(const int& number);

private:
  Type type_;
  Restriction restriction_;
};

} // namespace validator
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
