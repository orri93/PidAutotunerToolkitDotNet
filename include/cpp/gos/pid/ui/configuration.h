#ifndef GOS_PID_TUNING_UI_LIB_CONFIGURATION_H_
#define GOS_PID_TUNING_UI_LIB_CONFIGURATION_H_

#include <memory>

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <gos/pid/ui/types.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

class Base : public QObject {
  Q_OBJECT
public:
  explicit Base(QObject* parent = nullptr);

  virtual void initialize();

  virtual QSettings* read(QSettings* settings);
  virtual QSettings* write(QSettings* settings);

  const ::gos::pid::toolkit::ui::types::configuration::mode& mode() const;
  const ::gos::pid::toolkit::ui::types::configuration::mode& setMode(
  const ::gos::pid::toolkit::ui::types::configuration::mode& mode);

  const bool& isCompleted() const;

  const QString modeText() const;

  /* Mode helpers */
  void setNormal();

protected:

  template<typename T> bool canApplyPointer(T* internal, T* external) {
    return external != nullptr && external != internal;
  }

  template<typename T> bool applyPointer(T*& internal, T* external) {
    if (canApplyPointer(internal, external)) {
      internal = external;
      return true;
    }
    return false;
  }

  template<typename T> bool applyComparePointer(T*& internal, T* external) {
    if (canApplyPointer(internal, external)) {
      if (*internal != *external) {
        internal = external;
        return true;
      }
    }
    return false;
  }

  template<typename T> bool applyPointer(
    std::unique_ptr<T>& internal, T* external) {
    if (canApplyPointer(internal.get(), external)) {
      internal.reset(external);
      return true;
    }
    return false;
  }

  template<typename T> bool applyComparePointer(
    std::unique_ptr<T>& internal, T* external) {
    if (canApplyPointer(internal.get(), external)) {
      if (*internal != *external) {
        internal.reset(external);
        return true;
      }
    }
    return false;
  }


  bool iscompleted_;
  ::gos::pid::toolkit::ui::types::configuration::mode mode_;
};

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
