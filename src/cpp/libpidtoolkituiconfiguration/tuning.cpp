#include <algorithm>

#include <gos/pid/ui/configuration/tuning.h>

/* Tuning configuration */
#define GROUP_TUNING "Tuning"
#define KEY_TUNING_METHOD "Method"

/* PID configuration */
#define KEY_TUNING_KP "Kp"
#define KEY_TUNING_KI "Ki"
#define KEY_TUNING_KD "Kd"
#define DEFAULT_TUNING_KP 1.0
#define DEFAULT_TUNING_KI 0.01
#define DEFAULT_TUNING_KD 0.1

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

Tuning::Tuning(QObject* parent) :
  //gptum::Ptu(parent)
  gptum::Tuning(parent) {
}

Tuning::Tuning(const Tuning& tuning) :
  gptum::Tuning(dynamic_cast<const gptum::Tuning&>(tuning)),
  blackBox_(tuning.blackBox_) {
}

Tuning& Tuning::operator=(const Tuning& tuning) {
  return set(tuning);
}

Tuning& Tuning::set(const Tuning& tuning) {
  if (this != &tuning) {
    gptum::Tuning::set(dynamic_cast<const gptum::Tuning&>(tuning));
    blackBox_ = tuning.blackBox_;
  }
  return *this;
}

QSettings* Tuning::read(QSettings* settings) {
  QVariant value;

  /* Tuning configuration group */
  settings->beginGroup(GROUP_TUNING);

  gptum::tuning::Method::EnumerateModel& em =
    gptum::tuning::Method::enumerateModel();
  QString defaultmethodtext = em.toString(gptum::tuning::Method::Enum::None);
  value = settings->value(KEY_TUNING_METHOD, defaultmethodtext);
  gptum::tuning::Method::Enum method = em.parse(value.toString());
  setMethod(method);
  value = settings->value(KEY_TUNING_KP, DEFAULT_TUNING_KP);
  setKp(value.toDouble());
  value = settings->value(KEY_TUNING_KI, DEFAULT_TUNING_KI);
  setKi(value.toDouble());
  value = settings->value(KEY_TUNING_KD, DEFAULT_TUNING_KD);
  setKd(value.toDouble());

  /* TUNING configuration group */
  settings->endGroup();

  blackBox_.read(settings);

  return settings;
}

QSettings* Tuning::write(QSettings* settings) {

  /* Tuning configuration group */
  settings->beginGroup(GROUP_TUNING);
  gptum::tuning::Method::EnumerateModel& em =
    gptum::tuning::Method::enumerateModel();
  QString methodtext = em.toString(method_);
  settings->setValue(KEY_TUNING_METHOD, methodtext);
  settings->setValue(KEY_TUNING_KP, triplet_.kp());
  settings->setValue(KEY_TUNING_KI, triplet_.ki());
  settings->setValue(KEY_TUNING_KD, triplet_.kd());
  /* TUNING configuration group */
  settings->endGroup();

  blackBox_.write(settings);

  return settings;
}

BlackBox* Tuning::blackBox() { return &blackBox_; }
BlackBox& Tuning::getBlackBox() { return blackBox_; }

bool Tuning::applyBlackBox(const BlackBox* blackBox) {
  if (blackBox != nullptr && compare(blackBox_, *blackBox) != 0) {
    blackBox_ = *blackBox;
    return true;
  } else {
    return false;
  }
}

/* Tunings configuration */
void Tuning::setMethod(const gptum::tuning::Method::Enum& method) {
  if (applyMethod(method)) {
    emit methodChanged();
  }
}

void Tuning::setKp(const double& value) {
  if (applyKp(value)) {
    emit kpChanged();
  }
}
void Tuning::setKi(const double& value) {
  if (applyKi(value)) {
    emit kiChanged();
  }
}
void Tuning::setKd(const double& value) {
  if (applyKd(value)) {
    emit kdChanged();
  }
}

void Tuning::setBlackBox(const BlackBox* blackBox) {
  if (applyBlackBox(blackBox)) {
    emit blackBoxChanged();
  }
}


} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptuc::Tuning& lhs, const gptuc::Tuning& rhs) {
  return compare(lhs, rhs) == 0;
}
bool operator!=(const gptuc::Tuning& lhs, const gptuc::Tuning& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptuc::Tuning& first, const gptuc::Tuning& second) {
  return (
    /* Tuning output items */
    first.method_ == second.method_) ?
    0 : 1;
}
