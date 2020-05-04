#ifndef GOS_PID_TUNING_UI_FLOAT_VALIDATOR_H_
#define GOS_PID_TUNING_UI_FLOAT_VALIDATOR_H_

#include <QValidator>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace validator {

class Float : public QValidator {
  Q_OBJECT
public:
  explicit Float(QObject* parent = nullptr);
  virtual State validate(QString& input, int& pos) const;
};

} // namespace validator
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
