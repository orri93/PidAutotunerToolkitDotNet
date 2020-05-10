#ifndef GOS_PID_TUNING_UI_RANGE_H_
#define GOS_PID_TUNING_UI_RANGE_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/configuration.h>

#define GOS_QML_TYPE_RANGE_NAME "PidRange"
#define GOS_QML_TYPE_RANGE_URI GOS_QML_TYPE_RANGE_NAME

namespace gos { namespace pid { namespace toolkit { namespace ui {
class Range; } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::Range& lhs,
  const ::gos::pid::toolkit::ui::Range& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::Range& lhs,
  const ::gos::pid::toolkit::ui::Range& rhs);

int compare(
  const ::gos::pid::toolkit::ui::Range& first,
  const ::gos::pid::toolkit::ui::Range& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

class Range : public ::gos::pid::toolkit::ui::configuration::Base {
  Q_OBJECT
  Q_PROPERTY(double minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
  Q_PROPERTY(double maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)

  friend bool(::operator==) (const Range& lhs, const Range& rhs);
  friend bool(::operator!=) (const Range& lhs, const Range& rhs);
  friend int(::compare) (const Range& first, const Range& second);

public:
  explicit Range(QObject* parent = nullptr);
  Range(const double& minimum, const double& maximum, QObject* parent = nullptr);
  Range(const Range& range);

  Range& operator=(const Range& range);

  void set(const double& minimum, const double& maximum);
  
  const double& minimum() const;
  const double& maximum() const;

signals:
  void minimumChanged();
  void maximumChanged();

public slots:
  void setMinimum(const double& value);
  void setMaximum(const double& value);

private:
  double minimum_;
  double maximum_;
};

Range make_range(const double& minimum, const double& maximum);

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(
  const ::gos::pid::toolkit::ui::Range& lhs,
  const ::gos::pid::toolkit::ui::Range& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::Range& lhs,
  const ::gos::pid::toolkit::ui::Range& rhs);


#endif
