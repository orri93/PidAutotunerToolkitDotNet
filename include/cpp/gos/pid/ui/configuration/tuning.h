#ifndef GOS_PID_TUNING_UI_CONFIGURATION_TUNING_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_TUNING_H_

#include <memory>
#include <vector>

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QDebug>

#include <gos/pid/ui/model/tuning.h>

#include <gos/pid/ui/configuration/blackbox.h>

#define GOS_QML_TYPE_TUNING_NAME "TuningSetting"
#define GOS_QML_TYPE_TUNING_URI GOS_QML_TYPE_TUNING_NAME

namespace gos { namespace pid {namespace toolkit {namespace ui { 
namespace configuration { class Tuning; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::configuration::Tuning& lhs,
  const ::gos::pid::toolkit::ui::configuration::Tuning& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::configuration::Tuning& lhs,
  const ::gos::pid::toolkit::ui::configuration::Tuning& rhs);

int compare(
  const ::gos::pid::toolkit::ui::configuration::Tuning& first,
  const ::gos::pid::toolkit::ui::configuration::Tuning& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

class Tuning : public ::gos::pid::toolkit::ui::model::Tuning {
  Q_OBJECT

  /* Tuning configuration */
  //Q_PROPERTY(::gos::pid::toolkit::ui::model::tuning::Method::Enum tuning READ tuning WRITE setTuning NOTIFY tuningChanged)
  //Q_PROPERTY(QString tuningText READ tuningText WRITE setTuningText)
  Q_PROPERTY(BlackBox* blackBox READ blackBox WRITE setBlackBox NOTIFY blackBoxChanged)

  friend bool (::operator==) (const Tuning&, const Tuning&);
  friend bool (::operator!=) (const Tuning&, const Tuning&);
  friend int(::compare) (const Tuning&, const Tuning&);

public:

  explicit Tuning(QObject* parent = nullptr);
  Tuning(const Tuning& tuning);

  Tuning& operator=(const Tuning& tuning);

  Tuning& set(const Tuning& tuning);

  QSettings* read(QSettings* settings);
  QSettings* write(QSettings* settings);

  BlackBox* blackBox();
  BlackBox& getBlackBox();

  bool applyBlackBox(const BlackBox* blackBox);

signals:
  void blackBoxChanged();

public slots:
  /* Tuning configuration */
  void setMethod(
    const ::gos::pid::toolkit::ui::model::tuning::Method::Enum& method);

  void setKp(const double& value);
  void setKi(const double& value);
  void setKd(const double& value);

  void setBlackBox(const BlackBox* blackBox);

protected:
  void create();

  BlackBox blackBox_;
};

typedef std::unique_ptr<Tuning> TuningPointer;

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos


#endif
