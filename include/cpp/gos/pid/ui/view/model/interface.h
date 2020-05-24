#ifndef GOS_PID_TUNING_UI_VIEW_MODEL_INTERFACE_H_
#define GOS_PID_TUNING_UI_VIEW_MODEL_INTERFACE_H_

#include <gos/pid/ui/configuration/interface.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace view {
namespace model {

/**
 * @brief An interface for the View Models.
*/
class Interface {
public:
  virtual ~Interface() {}

  /**
   * @brief Apply updated configuration to a View Models.
   * @param configuration A updated top configuration interface.
   * @return true if the configuration was applied successfully otherwise false.
  */
  virtual bool apply(
    ::gos::pid::toolkit::ui::configuration::Interface& configuration) = 0;

  /**
   * @brief Notify a View Model that the QML panel is Completed. View Models can emit Changes
  */
  virtual void notify() = 0;
};

} // namespace model
} // namespace view
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos


#endif
