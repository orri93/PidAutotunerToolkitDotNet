#include <algorithm>

#include <gos/pid/ui/configuration/controller.h>

/* CONTROLLER configuration group */
#define GROUP_CONTROLLER "Controller"

/* Controller input items */

/* Controller output items */
#define KEY_BB_TEMPERATURE "Temperature"
#define KEY_BB_INTEGRAL "Integral"
#define DEFAULT_BB_TEMPERATURE_FROM 0.0
#define DEFAULT_BB_TEMPERATURE_TO 320.0

/* PID configuration */

/* Tuning configuration */

/* Evaluation configuration */

/* Other CONTROLLER configuration */

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

Controller::Controller(QObject* parent) :
  gptum::Ptu(parent) {
}

Controller::Controller(const Controller& controller) :
  /* Controller output items */
  temperature_(controller.temperature_),
  integral_(controller.integral_){
}

Controller& Controller::operator=(const Controller& controller) {
  return set(controller);
}

Controller& Controller::set(const Controller& controller) {
  if (this != &controller) {
    /* Controller output items */
    this->temperature_ = controller.temperature_;
    this->integral_ = controller.integral_;
  }
  return *this;
}

QSettings* Controller::read(QSettings* settings) {
  QVariant value;

  /* Controller configuration group */
  settings->beginGroup(GROUP_CONTROLLER);

  /* Controller input items */
  gptum::read(
    settings,
    KEY_BB_TEMPERATURE,
    temperature_,
    gptum::make_number(DEFAULT_BB_TEMPERATURE_FROM, DEFAULT_BB_TEMPERATURE_TO));
  gptum::read(
    settings,
    KEY_BB_INTEGRAL,
    temperature_,
    gptum::make_number());

  /* CONTROLLER configuration group */
  settings->endGroup();

  return settings;
}

QSettings* Controller::write(QSettings* settings) {

  /* Controller configuration group */
  settings->beginGroup(GROUP_CONTROLLER);

    /* Controller input items */
  gptum::write(
    settings,
    KEY_BB_TEMPERATURE,
    temperature_);
  gptum::write(
    settings,
    KEY_BB_INTEGRAL,
    temperature_);

  /* CONTROLLER configuration group */
  settings->endGroup();

  return settings;
}

/* Controller output items */
gptum::Number* Controller::temperature() { return &temperature_; }
gptum::Number* Controller::integral() { return &integral_; }

/* Controller output items */
void Controller::setTemperature(gptum::Number* number) {
  if (number != nullptr) {
    if (temperature_ != *number) {
      temperature_ = *number;
      emit temperatureChanged();
    }
  }
}
void Controller::setIntegral(gptum::Number* number) {
  if (number != nullptr) {
    if (integral_ != *number) {
      integral_ = *number;
      emit integralChanged();
    }
  }
}

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptuc::Controller& lhs, const gptuc::Controller& rhs) {
  return compare(lhs, rhs) == 0;
}
bool operator!=(const gptuc::Controller& lhs, const gptuc::Controller& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptuc::Controller& first, const gptuc::Controller& second) {
  return (
    /* Controller output items */
    first.temperature_ == second.temperature_ &&
    first.integral_ == second.integral_) ? 0 : 1;
}
