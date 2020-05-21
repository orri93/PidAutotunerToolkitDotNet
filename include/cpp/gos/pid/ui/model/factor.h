#ifndef GOS_PID_TUNING_UI_FACTOR_H_
#define GOS_PID_TUNING_UI_FACTOR_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/ptu.h>
#include <gos/pid/ui/model/operation.h>

#define GOS_QML_TYPE_FACTOR_NAME "PidFactor"
#define GOS_QML_TYPE_FACTOR_URI GOS_QML_TYPE_FACTOR_NAME

#define KEY_BB_FACTOR_IS_INCLUDED "FactorIsIncluded"
#define KEY_BB_FACTOR_VALUE "Factor"
#define KEY_BB_FACTOR_OPERATION "FactorOperation"
#define KEY_BB_FACTOR_IS_REVERSE "FactorIsReverse"
#define KEY_BB_FACTOR_REVERSE "FactorReverse"

#define DEFAULT_BB_FACTOR_IS_INCLUDED true
#define DEFAULT_BB_FACTOR_VALUE 1.0
#define DEFAULT_BB_FACTOR_OPERATION "Add"
#define DEFAULT_BB_FACTOR_IS_REVERSE false
#define DEFAULT_BB_FACTOR_REVERSE 0.0

namespace gos { namespace pid { namespace toolkit { namespace ui {
namespace model { class Factor; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::model::Factor& lhs,
  const ::gos::pid::toolkit::ui::model::Factor& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::model::Factor& lhs,
  const ::gos::pid::toolkit::ui::model::Factor& rhs);

int compare(
  const ::gos::pid::toolkit::ui::model::Factor& first,
  const ::gos::pid::toolkit::ui::model::Factor& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

QSettings* read(QSettings* settings, const QString& key, Factor& factor);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Factor& factor,
  const Factor& default);
QSettings* write(QSettings* settings,const QString& key, const Factor& factor);

class Factor : public Ptu {
  Q_OBJECT
  Q_PROPERTY(bool isIncluded MEMBER isIncluded_ WRITE setIsIncluded NOTIFY isIncludedChanged)
  Q_PROPERTY(double value MEMBER value_ WRITE setValue NOTIFY valueChanged)
  Q_PROPERTY(Operation::Enum operation MEMBER operation_ WRITE setOperation NOTIFY operationChanged)
  Q_PROPERTY(bool isReverse MEMBER isReverse_ WRITE setIsReverse NOTIFY isReverseChanged)
  Q_PROPERTY(double reverse MEMBER reverse_ WRITE setReverse NOTIFY reverseChanged)

  friend bool(::operator==) (const Factor& lhs, const Factor& rhs);
  friend bool(::operator!=) (const Factor& lhs, const Factor& rhs);
  friend int(::compare) (const Factor& first, const Factor& second);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Factor& factor);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Factor& factor,
    const Factor& default);
  friend QSettings* write(
    QSettings* settings,
    const QString& key,
    const Factor& factor);

public:
  explicit Factor(QObject* parent = nullptr);
  Factor(
    const bool& isIncluded,
    const double& value,
    const Operation::Enum& operation,
    const bool& isReverse,
    const double& reverse,
    QObject* parent = nullptr);
  Factor(const Factor& factor);
  Factor& operator=(const Factor& factor);

  Factor& set(const Factor& factor);

signals:
  void isIncludedChanged();
  void valueChanged();
  void operationChanged();
  void isReverseChanged();
  void reverseChanged();

public slots:
  void setIsIncluded(const bool& value);
  void setValue(const double& value);
  void setOperation(const Operation::Enum& value);
  void setIsReverse(const bool& value);
  void setReverse(const double& value);

private:
  bool isIncluded_;
  double value_;
  Operation::Enum operation_;
  bool isReverse_;
  double reverse_;
};

Factor make_factor(
  const bool& isIncluded,
  const double& value,
  const Operation::Enum& operation,
  const bool& isReverse,
  const double& reverse);

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
