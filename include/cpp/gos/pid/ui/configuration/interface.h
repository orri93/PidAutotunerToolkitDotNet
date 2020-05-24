#ifndef GOS_PID_TUNING_UI_CONFIGURATION_INTERFACE_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_INTERFACE_H_

#include <gos/pid/ui/configuration/controller.h>
#include <gos/pid/ui/configuration/modbus.h>
#include <gos/pid/ui/configuration/tuning.h>
#include <gos/pid/ui/configuration/timer.h>
#include <gos/pid/ui/configuration/ui.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

class Interface {
public:
  virtual ~Interface() {}

  /* Controller configuration */
  virtual ::gos::pid::toolkit::ui::configuration::Controller& getController() = 0;

  /* Modbus configuration */
  virtual ::gos::pid::toolkit::ui::configuration::Modbus& getModbus() = 0;

  /* Timers configuration */
  virtual ::gos::pid::toolkit::ui::configuration::Timer& getTimer() = 0;

  /* Tuning configuration */
  virtual ::gos::pid::toolkit::ui::configuration::Tuning& getTuning() = 0;

  /* UI configuration */
  virtual ::gos::pid::toolkit::ui::configuration::Ui& getUi() = 0;
};

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos


#endif
