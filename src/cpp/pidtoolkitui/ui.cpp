#include <algorithm>
#include <ui.h>

/* UI configuration group */
#define GROUP_UI "Ui"

/* Controller input items */
#define KEY_BB_SETPOINT "NumberSetpoint"
#define DEFAULT_BB_SETPOINT_MINIMUM 0.0
#define DEFAULT_BB_SETPOINT_MAXIMUM 320.0
#define DEFAULT_BB_SETPOINT_PRECISION 1
#define DEFAULT_BB_SETPOINT_STEP_SIZE 0.1

/* Controller output items */
#define KEY_BB_TEMPERATURE "NumberTemperature"
#define KEY_BB_INTEGRAL "NumberIntegral"
#define DEFAULT_BB_TEMPERATURE_MINIMUM 0.0
#define DEFAULT_BB_TEMPERATURE_MAXIMUM 320.0
#define DEFAULT_BB_TEMPERATURE_PRECISION 1
#define DEFAULT_BB_TEMPERATURE_STEP_SIZE 0.1
#define DEFAULT_BB_INTEGRAL_PRECISION 0
#define DEFAULT_BB_INTEGRAL_STEP_SIZE 1

/* PID configuration */
#define KEY_BB_KP "NumberKp"
#define KEY_BB_KI "NumberKi"
#define KEY_BB_KD "NumberKd"
#define DEFAULT_BB_KP_MINIMUM 0.0
#define DEFAULT_BB_KP_MAXIMUM 10.0
#define DEFAULT_BB_KP_PRECISION 2
#define DEFAULT_BB_KP_STEP_SIZE 0.01
#define DEFAULT_BB_KI_MINIMUM 0.0
#define DEFAULT_BB_KI_MAXIMUM 1.0
#define DEFAULT_BB_KI_PRECISION 4
#define DEFAULT_BB_KI_STEP_SIZE 0.0001
#define DEFAULT_BB_KD_MINIMUM 0.0
#define DEFAULT_BB_KD_MAXIMUM 10.0
#define DEFAULT_BB_KD_PRECISION 3
#define DEFAULT_BB_KD_STEP_SIZE 0.001

/* Tuning configuration */
#define KEY_BB_KP_TUNING "RangeKpTuning"
#define KEY_BB_KI_TUNING "RangeKiTuning"
#define DEFAULT_BB_KP_TUNING_MINIMUM 0.0
#define DEFAULT_BB_KP_TUNING_MAXIMUM 1.0
#define DEFAULT_BB_KI_TUNING_MINIMUM 0.0
#define DEFAULT_BB_KI_TUNING_MAXIMUM 10.0

/* Evaluation configuration */
#define KEY_BB_FACTOR "NumberFactor"
#define DEFAULT_BB_FACTOR_PRECISION 3
#define DEFAULT_BB_FACTOR_STEP_SIZE 0.001

/* Other UI configuration */
#define KEY_BB_SD "NumberSd"
#define KEY_BB_CHART "NumberChart"
#define DEFAULT_BB_SD_MINIMUM 0.0
#define DEFAULT_BB_SD_MAXIMUM 10.0
#define DEFAULT_BB_SD_PRECISION 4
#define DEFAULT_BB_SD_STEP_SIZE 0.0001
#define DEFAULT_BB_CHART_MINIMUM 0.0
#define DEFAULT_BB_CHART_MAXIMUM 320.0
#define DEFAULT_BB_CHART_PRECISION 1
#define DEFAULT_BB_CHART_STEP_SIZE 0.1

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

Ui::Ui(QObject* parent) :
  gptuc::Base(parent),
  /* Controller output items */
  integral_(false),
  /* Evaluation configuration */
  factor_(false) {
}

Ui::Ui(const Ui& ui) :
  /* Controller input items */
  setpoint_(ui.setpoint_),
  /* Controller output items */
  temperature_(ui.temperature_),
  integral_(ui.integral_),
  /* PID configuration */
  kp_(ui.kp_),
  ki_(ui.ki_),
  kd_(ui.kd_),
  /* Tuning configuration */
  kpTuning_(ui.kpTuning_),
  kiTuning_(ui.kiTuning_),
  /* Evaluation configuration */
  factor_(ui.factor_),
  /* Other UI configuration */
  sd_(ui.sd_),
  chart_(ui.chart_) {
}

Ui& Ui::operator=(const Ui& ui) {
  return set(ui);
}

Ui& Ui::set(const Ui& ui) {
  if (this != &ui) {
    /* Controller input items */
    this->setpoint_ = ui.setpoint_;

    /* Controller output items */
    this->temperature_ = ui.temperature_;
    this->integral_ = ui.integral_;

    /* PID configuration */
    this->kp_ = ui.kp_;
    this->ki_ = ui.ki_;
    this->kd_ = ui.kd_;

    /* Tuning configuration */
    this->kpTuning_ = ui.kpTuning_;
    this->kiTuning_ = ui.kiTuning_;

    /* Evaluation configuration */
    this->factor_ = ui.factor_;

    /* Other UI configuration */
    this->sd_ = ui.sd_;
    this->chart_ = ui.chart_;
  }
  return *this;
}

QSettings* Ui::read(QSettings* settings) {
  QVariant value;

  /* Ui configuration group */
  settings->beginGroup(GROUP_UI);

  /* Controller input items */
  gptu::read(
    settings,
    KEY_BB_SETPOINT,
    setpoint_,
    DEFAULT_BB_SETPOINT_MINIMUM,
    DEFAULT_BB_SETPOINT_MAXIMUM,
    DEFAULT_BB_SETPOINT_PRECISION,
    DEFAULT_BB_SETPOINT_STEP_SIZE);

  /* Controller output items */
  gptu::read(
    settings,
    KEY_BB_TEMPERATURE,
    temperature_,
    DEFAULT_BB_TEMPERATURE_MINIMUM,
    DEFAULT_BB_TEMPERATURE_MAXIMUM,
    DEFAULT_BB_TEMPERATURE_PRECISION,
    DEFAULT_BB_TEMPERATURE_STEP_SIZE);
  gptu::read(
    settings,
    KEY_BB_INTEGRAL,
    integral_,
    DEFAULT_BB_INTEGRAL_PRECISION,
    DEFAULT_BB_INTEGRAL_STEP_SIZE);

  /* PID configuration */
  gptu::read(
    settings,
    KEY_BB_KP,
    kp_,
    DEFAULT_BB_KP_MINIMUM,
    DEFAULT_BB_KP_MAXIMUM,
    DEFAULT_BB_KP_PRECISION,
    DEFAULT_BB_KP_STEP_SIZE);
  gptu::read(
    settings,
    KEY_BB_KI,
    ki_,
    DEFAULT_BB_KI_MINIMUM,
    DEFAULT_BB_KI_MAXIMUM,
    DEFAULT_BB_KI_PRECISION,
    DEFAULT_BB_KI_STEP_SIZE);
  gptu::read(
    settings,
    KEY_BB_KD,
    kd_,
    DEFAULT_BB_KD_MINIMUM,
    DEFAULT_BB_KD_MAXIMUM,
    DEFAULT_BB_KD_PRECISION,
    DEFAULT_BB_KD_STEP_SIZE);

  /* Tuning configuration */
  gptu::read(
    settings,
    KEY_BB_KP_TUNING,
    this->kpTuning_,
    DEFAULT_BB_KP_TUNING_MINIMUM,
    DEFAULT_BB_KP_TUNING_MAXIMUM);
  gptu::read(
    settings,
    KEY_BB_KI_TUNING,
    this->kiTuning_,
    DEFAULT_BB_KI_TUNING_MINIMUM,
    DEFAULT_BB_KI_TUNING_MAXIMUM);

  /* Evaluation configuration */
  gptu::read(
    settings,
    KEY_BB_FACTOR,
    factor_,
    DEFAULT_BB_FACTOR_PRECISION,
    DEFAULT_BB_FACTOR_STEP_SIZE);

  /* Other UI configuration */
  gptu::read(
    settings,
    KEY_BB_SD,
    sd_,
    DEFAULT_BB_SD_MINIMUM,
    DEFAULT_BB_SD_MAXIMUM,
    DEFAULT_BB_SD_PRECISION,
    DEFAULT_BB_SD_STEP_SIZE);
  gptu::read(
    settings,
    KEY_BB_CHART,
    chart_,
    DEFAULT_BB_CHART_MINIMUM,
    DEFAULT_BB_CHART_MAXIMUM,
    DEFAULT_BB_CHART_PRECISION,
    DEFAULT_BB_CHART_STEP_SIZE);

  /* UI configuration group */
  settings->endGroup();

  return settings;
}

QSettings* Ui::write(QSettings* settings) {
  return settings;

  /* Ui configuration group */
  settings->beginGroup(GROUP_UI);

  /* Controller input items */
  gptu::write(settings, KEY_BB_SETPOINT, setpoint_);

  /* Controller output items */
  gptu::write(settings, KEY_BB_TEMPERATURE, temperature_);
  gptu::write(settings, KEY_BB_INTEGRAL, integral_);

  /* PID configuration */
  gptu::write(settings, KEY_BB_KP, kp_);
  gptu::write(settings, KEY_BB_KI, ki_);
  gptu::write(settings, KEY_BB_KD, kd_);

  /* Tuning configuration */
  gptu::write(settings, KEY_BB_KP_TUNING, this->kpTuning_);
  gptu::write(settings, KEY_BB_KI_TUNING, this->kiTuning_);

  /* Evaluation configuration */
  gptu::write(settings, KEY_BB_FACTOR, factor_);

  /* Other UI configuration */
  gptu::write(settings, KEY_BB_SD, sd_);
  gptu::write(settings, KEY_BB_CHART, chart_);

  /* UI configuration group */
  settings->endGroup();
}

/* Controller input items */
gptu::Number* Ui::setpoint() { return &setpoint_; }
/* Controller output items */
gptu::Number* Ui::temperature() { return &temperature_; }
gptu::Number* Ui::integral() { return &integral_; }
/* PID configuration */
gptu::Number* Ui::kp() { return &kp_; }
gptu::Number* Ui::ki() { return &ki_; }
gptu::Number* Ui::kd() { return &kd_; }
/* Tuning configuration */
gptu::Range* Ui::kpTuning() { return &kpTuning_; }
gptu::Range* Ui::kiTuning() { return &kiTuning_; }
/* Evaluation configuration */
gptu::Number* Ui::factor() { return &factor_; }
/* Other UI configuration */
gptu::Number* Ui::sd() { return &sd_; }
gptu::Number* Ui::chart() { return &chart_; }

/* Controller input items */
void Ui::setSetpoint(gptu::Number* number) {
  if (number != nullptr) {
    if (setpoint_ != *number) {
      setpoint_ = *number;
      emit setpointChanged();
    }
  }
}
/* Controller output items */
void Ui::setTemperature(gptu::Number* number) {
  if (number != nullptr) {
    if (temperature_ != *number) {
      temperature_ = *number;
      emit temperatureChanged();
    }
  }
}
void Ui::setIntegral(gptu::Number* number) {
  if (number != nullptr) {
    if (integral_ != *number) {
      integral_ = *number;
      emit integralChanged();
    }
  }
}
/* PID configuration */
void Ui::setKp(gptu::Number* number) {
  if (number != nullptr) {
    if (kp_ != *number) {
      kp_ = *number;
      emit kpChanged();
    }
  }
}
void Ui::setKi(gptu::Number* number) {
  if (number != nullptr) {
    if (ki_ != *number) {
      ki_ = *number;
      emit kiChanged();
    }
  }
}
void Ui::setKd(gptu::Number* number) {
  if (number != nullptr) {
    if (kd_ != *number) {
      kd_ = *number;
      emit kdChanged();
    }
  }
}
/* Tuning configuration */
void Ui::setKpTuning(gptu::Range* range) {
  if (range != nullptr) {
    if (kpTuning_ != *range) {
      kpTuning_ = *range;
      emit kpTuningChanged();
    }
  }
}
void Ui::setKiTuning(gptu::Range* range) {
  if (range != nullptr) {
    if (kiTuning_ != *range) {
      kiTuning_ = *range;
      emit kiTuningChanged();
    }
  }
}
/* Evaluation configuration */
void Ui::setFactor(gptu::Number* number) {
  if (number != nullptr) {
    if (factor_ != *number) {
      factor_ = *number;
      emit factorChanged();
    }
  }
}
/* Other UI configuration */
void Ui::setSd(gptu::Number* number) {
  if (number != nullptr) {
    if (sd_ != *number) {
      sd_ = *number;
      emit sdChanged();
    }
  }
}
void Ui::setChart(gptu::Number* number) {
  if (number != nullptr) {
    if (chart_ != *number) {
      chart_ = *number;
      emit chartChanged();
    }
  }
}

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptuc::Ui& lhs, const gptuc::Ui& rhs) {
  return compare(lhs, rhs) == 0;
}
bool operator!=(const gptuc::Ui& lhs, const gptuc::Ui& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptuc::Ui& first, const gptuc::Ui& second) {
  return (
    /* Controller input items */
    first.setpoint_ == second.setpoint_ &&
    /* Controller output items */
    first.temperature_ == second.temperature_ &&
    first.integral_ == second.integral_ &&
    /* PID configuration */
    first.kp_ == second.kp_ &&
    first.ki_ == second.ki_ &&
    first.kd_ == second.kd_ &&
    /* Tuning configuration */
    first.kpTuning_ == second.kpTuning_ &&
    first.kiTuning_ == second.kiTuning_ &&
    /* Evaluation configuration */
    first.factor_ == second.factor_ &&
    /* Other UI configuration */
    first.sd_ == second.sd_ &&
    first.chart_ == second.chart_) ? 0 : 1;
}
