#ifndef GOS_PID_TUNING_UI_MODEL_NUMBER_H_
#define GOS_PID_TUNING_UI_MODEL_NUMBER_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/range.h>
#include <gos/pid/ui/model/restriction.h>

#define KEY_BB_NUMBER_RANGE "Range"
#define KEY_BB_NUMBER_RESTRICTION "Restriction"

namespace gos { namespace pid { namespace toolkit { namespace ui {
namespace model { class Number; } } } } }

int compare(
  const ::gos::pid::toolkit::ui::model::Number& first,
  const ::gos::pid::toolkit::ui::model::Number& second);

bool operator==(
  const ::gos::pid::toolkit::ui::model::Number& lhs,
  const ::gos::pid::toolkit::ui::model::Number& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::model::Number& lhs,
  const ::gos::pid::toolkit::ui::model::Number& rhs);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

QSettings* read(QSettings* settings, const QString& key, Number& number);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Number& number,
  const Restriction::Enum& restriction,
  const Range& range);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Number& number,
  const Number& default);
QSettings* write(
  QSettings * settings,
  const QString & key,
  const Number & number);

class Number : public QObject {
  Q_OBJECT

  Q_PROPERTY(Range* range READ range WRITE setRange NOTIFY rangeChanged)
  Q_PROPERTY(Restriction::Enum restriction MEMBER restriction_ WRITE setRestriction NOTIFY restrictionChanged)

  friend bool(::operator==) (const Number& lhs, const Number& rhs);
  friend bool(::operator!=) (const Number& lhs, const Number& rhs);
  friend int(::compare) (const Number& first, const Number& second);

  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Number& number);
  friend QSettings* read(
    QSettings * settings,
    const QString & key,
    Number & number,
    const Restriction::Enum& restriction,
    const Range& range);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Number& number,
    const Number& default);
  friend QSettings* write(
    QSettings * settings,
    const QString & key,
    const Number & number);

public:
  explicit Number(QObject* parent = nullptr);
  Number(
    const ::gos::pid::toolkit::ui::model::Restriction::Enum& restriction,
    const Range& range,
    QObject* parent = nullptr);
  Number(const double& from, const double& to, QObject* parent = nullptr);
  Number(const Number& number);
  Number& operator=(const Number& number);

  Number& set(const Number& number);
  void set(
    const ::gos::pid::toolkit::ui::model::Restriction::Enum& restriction,
    const Range& range);

  Range* range();

signals:
  void rangeChanged();
  void restrictionChanged();

public slots:
  void setRange(const Range* value);
  void setRestriction(
    const ::gos::pid::toolkit::ui::model::Restriction::Enum& value);

private:
  void setRange(const Range& value);

  Range range_;
  ::gos::pid::toolkit::ui::model::Restriction::Enum restriction_;
};

Number make_number();
Number make_number(
  const ::gos::pid::toolkit::ui::model::Restriction::Enum& restriction,
  const Range& range);
Number make_number(const double& from, const double& to);


} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
