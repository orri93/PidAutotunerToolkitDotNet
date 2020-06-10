#ifndef GOS_PID_TUNING_UI_MODELS_H_
#define GOS_PID_TUNING_UI_MODELS_H_

#include <QObject>
#include <QVariant>
#include <QtQml/QQmlContext>

#include <gos/pid/ui/model/restriction.h>
#include <gos/pid/ui/model/operation.h>
#include <gos/pid/ui/model/serial.h>
#include <gos/pid/ui/model/tuning.h>
#include <gos/pid/ui/model/status.h>
#include <gos/pid/ui/model/force.h>
#include <gos/pid/ui/model/ptu.h>

#include <gos/pid/ui/view/model/blackbox.h>
#include <gos/pid/ui/view/model/tuning.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

class Models;

namespace models {
bool create(QQmlContext& context);
Models& instance();
}

/**
 * @brief The Models Class
*/
class Models : public QObject {
  Q_OBJECT

  /* Lists */
   /*! \addtogroup listModels
   *  Additional documentation for group 'listModels'
   *  @{
   */
  Q_PROPERTY(QVariant interval READ interval)
  Q_PROPERTY(QVariant mode READ mode)
    /*! @} */

  /* Models */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::ptu::Status* ptuStatus READ ptuStatus)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Force* force READ force NOTIFY forceChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Status* status READ status)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::tuning::Method* tuningMethod READ tuningMethod NOTIFY tuningMethodChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Operation* operation READ operation)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Restriction* restriction READ restriction)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Serial* serialBaud READ serialBaud NOTIFY serialBaudChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Serial* serialPort READ serialPort NOTIFY serialPortChanged)

  /* View Models */
  Q_PROPERTY(::gos::pid::toolkit::ui::view::model::tuning::Status* tuningStatus READ tuningStatus)
  Q_PROPERTY(::gos::pid::toolkit::ui::view::model::black::box::State* blackBox READ blackBox)

public:
  Models(QObject* parent = nullptr);

  /**
   * @brief Initialize the Models.
   * @return true if successful otherwise false.
  */
  bool initialize();

  /* Lists */
  const QVariant& interval() const;
  const QVariant& mode() const;

  /* Models */
  ::gos::pid::toolkit::ui::model::ptu::Status* ptuStatus();
  ::gos::pid::toolkit::ui::model::Force* force();
  ::gos::pid::toolkit::ui::model::Status* status();
  ::gos::pid::toolkit::ui::model::tuning::Method* tuningMethod();
  ::gos::pid::toolkit::ui::model::Operation* operation();
  ::gos::pid::toolkit::ui::model::Restriction* restriction();
  ::gos::pid::toolkit::ui::model::Serial* serialBaud();
  ::gos::pid::toolkit::ui::model::Serial* serialPort();

  /* View Models  */
  ::gos::pid::toolkit::ui::view::model::tuning::Status* tuningStatus();
  ::gos::pid::toolkit::ui::view::model::black::box::State* blackBox();

  /* Models */
  ::gos::pid::toolkit::ui::model::Force& getForce();

signals:
  /* Models */
  void forceChanged();
  void tuningMethodChanged();
  void serialBaudChanged();
  void serialPortChanged();

private:
  /* Lists */
  QVariant operationmodel_;
  QVariant intervalmodel_;
  QVariant tuningmodel_;
  QVariant modemodel_;

  /* Models */
  ::gos::pid::toolkit::ui::model::ptu::Status ptuStatus_;
  ::gos::pid::toolkit::ui::model::Force force_;
  ::gos::pid::toolkit::ui::model::Status status_;
  ::gos::pid::toolkit::ui::model::tuning::Method tuningMethod_;
  ::gos::pid::toolkit::ui::model::Operation operation_;
  ::gos::pid::toolkit::ui::model::Restriction restriction_;
  ::gos::pid::toolkit::ui::model::Serial serialBaud_;
  ::gos::pid::toolkit::ui::model::Serial serialPort_;

  /* View Models */
  ::gos::pid::toolkit::ui::view::model::tuning::Status tuningStatus_;
  ::gos::pid::toolkit::ui::view::model::black::box::State blackBox_;
};

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif