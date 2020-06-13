#ifndef GOS_PID_TUNING_UI_CONFIGURATION_TIMER_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_TIMER_H_

#include <memory>
#include <vector>

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QDebug>

#include <gos/pid/ui/model/number.h>
#include <gos/pid/ui/model/ptu.h>

#define GOS_QML_TYPE_TIMER_NAME "TimerSetting"
#define GOS_QML_TYPE_TIMER_URI GOS_QML_TYPE_TIMER_NAME

namespace gos { namespace pid {namespace toolkit {namespace ui { 
namespace configuration { class Timer; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::configuration::Timer& lhs,
  const ::gos::pid::toolkit::ui::configuration::Timer& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::configuration::Timer& lhs,
  const ::gos::pid::toolkit::ui::configuration::Timer& rhs);

int compare(
  const ::gos::pid::toolkit::ui::configuration::Timer& first,
  const ::gos::pid::toolkit::ui::configuration::Timer& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

class Timer : public ::gos::pid::toolkit::ui::model::Ptu {
  Q_OBJECT

  /* Timers configuration */
  Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
  Q_PROPERTY(bool synchronizeWithController READ synchronizeWithController WRITE setSynchronizeWithController NOTIFY synchronizeWithControllerChanged)

  friend bool (::operator==) (const Timer&, const Timer&);
  friend bool (::operator!=) (const Timer&, const Timer&);
  friend int(::compare) (const Timer&, const Timer&);

public:

  explicit Timer(QObject* parent = nullptr);

  Timer(const Timer& timer);

  Timer& operator=(const Timer& timer);

  Timer& set(const Timer& timer);

  QSettings* read(QSettings* settings);
  QSettings* write(QSettings* settings);

  /* Timers configuration */
  const int& interval() const;
  const bool& synchronizeWithController() const;

  /* Timers configuration */
  bool applyInterval(const int& value);
  bool applySynchronizeWithController(const bool& value);

signals:
  /* Timers configuration */
  void intervalChanged();
  void synchronizeWithControllerChanged();

public slots:
  /* Timers configuration */
  void setInterval(const int& value);
  void setSynchronizeWithController(const bool& value);

protected:
  void create();

  /* Timers configuration */
  int interval_;
  bool synchronizeWithController_;
};

typedef std::unique_ptr<Timer> TimerPointer;

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos


#endif
