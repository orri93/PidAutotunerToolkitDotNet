#include <gos/pid/ui/model/ptu.h>

namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Ptu::Ptu(QObject* parent) :
  QObject(parent),
  iscompleted_(false),
  mode_(gptut::configuration::mode::normal) {
}

Ptu::~Ptu() {
}

bool Ptu::initialize() {
  mode_ = gptut::configuration::mode::initializing;
  iscompleted_ = true;
  return iscompleted_;
}

QSettings* Ptu::read(QSettings* settings) {
  return nullptr;
}

QSettings* Ptu::write(QSettings* settings) {
  return nullptr;
}

const gptut::configuration::mode& Ptu::mode() const {
  return mode_;
}

const gptut::configuration::mode& Ptu::setMode(
  const gptut::configuration::mode& mode) {
  return mode_ = mode;
}

const bool& Ptu::isCompleted() const {
  return iscompleted_;
}

const QString Ptu::modeText() const {
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

void Ptu::setNormal() {
  setMode(gptut::configuration::mode::normal);
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
