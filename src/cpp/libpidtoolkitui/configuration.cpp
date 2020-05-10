#include <gos/pid/ui/configuration.h>

namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

Base::Base(QObject* parent) :
  QObject(parent),
  iscompleted_(false),
  mode_(gptut::configuration::mode::normal) {
}

void Base::initialize() {
  mode_ = gptut::configuration::mode::initializing;
  iscompleted_ = true;
}

QSettings* Base::read(QSettings* settings) {
  return nullptr;
}

QSettings* Base::write(QSettings* settings) {
  return nullptr;
}

const gptut::configuration::mode& Base::mode() const {
  return mode_;
}

const gptut::configuration::mode& Base::setMode(
  const gptut::configuration::mode& mode) {
  return mode_ = mode;
}

const bool& Base::isCompleted() const {
  return iscompleted_;
}

const QString Base::modeText() const {
  switch (mode_) {
  case gptut::configuration::mode::initializing:
    return "initializing";
  case gptut::configuration::mode::normal:
    return "normal";
  case gptut::configuration::mode::write:
    return "write";
  default:
    return "unknown";
  }
}

void Base::setNormal() {
  setMode(gptut::configuration::mode::normal);
}

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
