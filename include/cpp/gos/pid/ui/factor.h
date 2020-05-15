#ifndef GOS_PID_TUNING_UI_FACTOR_H_
#define GOS_PID_TUNING_UI_FACTOR_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/configuration.h>
#include <gos/pid/ui/operation.h>

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

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

class Factor;
}
}
}
}

bool operator==(
  const ::gos::pid::toolkit::ui::Factor& lhs,
  const ::gos::pid::toolkit::ui::Factor& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::Factor& lhs,
  const ::gos::pid::toolkit::ui::Factor& rhs);

int compare(
  const ::gos::pid::toolkit::ui::Factor& first,
  const ::gos::pid::toolkit::ui::Factor& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

QSettings* read(QSettings* settings, const QString& key, Factor& factor);

QSettings* write(QSettings* settings,const QString& key, const Factor& factor);

class Factor : public ::gos::pid::toolkit::ui::configuration::Base {
  Q_OBJECT
  Q_PROPERTY(bool isIncluded READ isIncluded WRITE setIsIncluded NOTIFY isIncludedChanged)
  Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
  Q_PROPERTY(int operationIndex READ operationIndex WRITE setOperationIndex NOTIFY operationIndexChanged)
  Q_PROPERTY(bool isReverse READ isReverse WRITE setIsReverse NOTIFY isReverseChanged)
  Q_PROPERTY(double reverse READ reverse WRITE setReverse NOTIFY reverseChanged)

  friend bool(::operator==) (const Factor& lhs, const Factor& rhs);
  friend bool(::operator!=) (const Factor& lhs, const Factor& rhs);
  friend int(::compare) (const Factor& first, const Factor& second);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Factor& factor);
  friend QSettings* write(
    QSettings* settings,
    const QString& key,
    const Factor& factor);

public:
  explicit Factor(QObject* parent = nullptr);
  Factor(const Factor& factor);

  Factor& operator=(const Factor& factor);

  Factor& set(const Factor& factor);

  const bool& isIncluded() const;
  const double& value() const;
  const ::gos::pid::toolkit::ui::types::operation& operation() const;
  const int operationIndex() const;
  const bool& isReverse() const;
  const double& reverse() const;

signals:
  void isIncludedChanged();
  void valueChanged();
  void operationIndexChanged();
  void isReverseChanged();
  void reverseChanged();

public slots:
  void setIsIncluded(const bool& value);
  void setValue(const double& value);
  void setOperation(const gos::pid::toolkit::ui::types::operation& value);
  void setOperationIndex(const int& value);
  void setIsReverse(const bool& value);
  void setReverse(const double& value);

private:
  bool isIncluded_;
  double value_;
  ::gos::pid::toolkit::ui::types::operation operation_;
  bool isReverse_;
  double reverse_;
};

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
