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
public:

  explicit Path(QObject* parent = nullptr);
  virtual State validate(QString& input, int& pos) const;

  enum Type {
    PATH_VALIDATOR_ANY,
    PATH_VALIDATOR_DIRECTORY,
    PATH_VALIDATOR_FILE
  };
  Q_ENUMS(Type)

  const Type& type() const;

  void setType(const Type& type);

private:
  Type type_;
};

} // namespace validator
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
