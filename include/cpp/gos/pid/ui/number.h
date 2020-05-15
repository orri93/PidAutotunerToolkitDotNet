#ifndef GOS_PID_TUNING_UI_NUMBER_H_
#define GOS_PID_TUNING_UI_NUMBER_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/range.h>

#define GOS_QML_TYPE_NUMBER_NAME "PidNumber"
#define GOS_QML_TYPE_NUMBER_URI GOS_QML_TYPE_NUMBER_NAME

#define KEY_BB_NUMBER_PRECISION "Precision"
#define KEY_BB_NUMBER_STEP_SIZE "StepSize"

#define DEFAULT_BB_NUMBER_PRECISION 0
#define DEFAULT_BB_NUMBER_STEP_SIZE 1.0

namespace gos { namespace pid { namespace toolkit { namespace ui {
class Number; } } } }

int compare(
  const ::gos::pid::toolkit::ui::Number& first,
  const ::gos::pid::toolkit::ui::Number& second);

bool operator==(
  const ::gos::pid::toolkit::ui::Number& lhs,
  const ::gos::pid::toolkit::ui::Number& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::Number& lhs,
  const ::gos::pid::toolkit::ui::Number& rhs);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

QSettings* read(QSettings* settings, const QString& key, Number& number);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Number& range,
  const double& minimum,
  const double& maximum,
  const int& precision,
  const double& stepSize);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Number& range,
  const int& precision,
  const double& stepSize);
QSettings* write(QSettings* settings, const QString& key, const Number& number);


class Number : public ::gos::pid::toolkit::ui::Range {
  Q_OBJECT

  Q_PROPERTY(bool isLimit READ isLimit NOTIFY isLimitChanged)
  Q_PROPERTY(int precision READ precision WRITE setPrecision NOTIFY precisionChanged)
  Q_PROPERTY(double stepSize READ stepSize WRITE setStepSize NOTIFY stepSizeChanged)

  friend bool(::operator==) (const Number& lhs, const Number& rhs);
  friend bool(::operator!=) (const Number& lhs, const Number& rhs);
  friend int(::compare) (const Number& first, const Number& second);

  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Number& number);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Number& number,
    const double& minimum,
    const double& maximum,
    const int& precision,
    const double& stepSize);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Number& number,
    const int& precision,
    const double& stepSize);
  friend QSettings* write(
    QSettings* settings,
    const QString& key,
    const Number& number);

public:
  explicit Number(QObject* parent = nullptr);
  Number(const bool& isLimit, QObject* parent = nullptr);
  Number(
    const double& minimum,
    const double& maximum,
    const int& precision,
    const double& stepSize,
    QObject* parent = nullptr);
  Number(
    const int& precision,
    const double& stepSize,
    QObject* parent = nullptr);
  Number(const Number& range);
  Number& operator=(const Number& range);

  Number& set(const Number& range);
  void set(
    const double& minimum,
    const double& maximum,
    const int& precision,
    const double& stepSize);
  void set(
    const int& precision,
    const double& stepSize);

  const bool& isLimit() const;
  const int& precision() const;
  const double& stepSize() const;

signals:
  void isLimitChanged();
  void precisionChanged();
  void stepSizeChanged();

public slots:
  void setPrecision(const int& value);
  void setStepSize(const double& value);

private:
  void setIsLimit(const bool& value);

  bool isLimit_;
  int precision_;
  double stepSize_;
};

Number make_number(
  const double& minimum,
  const double& maximum,
  const int& precision,
  const double& stepSize);

Number make_number(
  const int& precision,
  const double& stepSize);

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
