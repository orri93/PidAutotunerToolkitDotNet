#include <algorithm>
#include <ui.h>

/* UI configuration group */
#define GROUP_UI "Ui"

/* Controller input items */
#define KEY_BB_SETPOINT "NumberSetpoint"
#define DEFAULT_BB_SETPOINT_MINIMUM 0.0
#define DEFAULT_BB_SETPOINT_MAXIMUM 320.0
#define DEFAULT_BB_SETPOINT_PRECISION 1

/* Controller output items */
#define KEY_BB_TEMPERATURE "NumberTemperature"
#define KEY_BB_INTEGRAL "NumberIntegral"
#define DEFAULT_BB_TEMPERATURE_MINIMUM 0.0
#define DEFAULT_BB_TEMPERATURE_MAXIMUM 320.0
#define DEFAULT_BB_TEMPERATURE_PRECISION 1
#define DEFAULT_BB_INTEGRAL_PRECISION 0

/* PID configuration */
#define KEY_BB_KP "NumberKp"
#define KEY_BB_KI "NumberKi"
#define KEY_BB_KD "NumberKd"
#define DEFAULT_BB_KP_MINIMUM 0.0
#define DEFAULT_BB_KP_MAXIMUM 10.0
#define DEFAULT_BB_KP_PRECISION 2
#define DEFAULT_BB_KI_MINIMUM 0.0
#define DEFAULT_BB_KI_MAXIMUM 1.0
#define DEFAULT_BB_KI_PRECISION 4
#define DEFAULT_BB_KD_MINIMUM 0.0
#define DEFAULT_BB_KD_MAXIMUM 10.0
#define DEFAULT_BB_KD_PRECISION 3

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

/* Other UI configuration */
#define KEY_BB_SD "NumberSd"
#define KEY_BB_CHART "NumberChart"
#define DEFAULT_BB_SD_MINIMUM 0.0
#define DEFAULT_BB_SD_MAXIMUM 10.0
#define DEFAULT_BB_SD_PRECISION 4
#define DEFAULT_BB_CHART_MINIMUM 0.0
#define DEFAULT_BB_CHART_MAXIMUM 320.0
#define DEFAULT_BB_CHART_PRECISION 1

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

Ui::Ui(QObject* parent) :
  gptum::Ptu(parent) {
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
  gptum::read(
    settings,
    KEY_BB_SETPOINT,
    setpoint_,
    gptum::make_accuracy(
      gptum::Restriction::Enum::Both,
      gptum::make_range(
        DEFAULT_BB_SETPOINT_MINIMUM,
        DEFAULT_BB_SETPOINT_MAXIMUM),
      DEFAULT_BB_SETPOINT_PRECISION));

  /* Controller output items */
  gptum::read(
    settings,
    KEY_BB_TEMPERATURE,
    temperature_,
    DEFAULT_BB_TEMPERATURE_PRECISION);
  gptum::read(
    settings,
    KEY_BB_INTEGRAL,
    integral_,
    DEFAULT_BB_INTEGRAL_PRECISION);

  /* PID configuration */
  gptum::read(
    settings,
    KEY_BB_KP,
    kp_,
    gptum::make_accuracy(
      gptum::Restriction::Enum::Both,
      gptum::make_range(
        DEFAULT_BB_KP_MINIMUM,
        DEFAULT_BB_KP_MAXIMUM),
      DEFAULT_BB_KP_PRECISION));
  gptum::read(
    settings,
    KEY_BB_KI,
    ki_,
    gptum::make_accuracy(
      gptum::Restriction::Enum::Both,
      gptum::make_range(
        DEFAULT_BB_KI_MINIMUM,
        DEFAULT_BB_KI_MAXIMUM),
      DEFAULT_BB_KI_PRECISION));
  gptum::read(
    settings,
    KEY_BB_KD,
    kd_,
    gptum::make_accuracy(
      gptum::Restriction::Enum::Both,
      gptum::make_range(
        DEFAULT_BB_KD_MINIMUM,
        DEFAULT_BB_KD_MAXIMUM),
      DEFAULT_BB_KD_PRECISION));

  /* Tuning configuration */
  gptum::read(
    settings,
    KEY_BB_KP_TUNING,
    this->kpTuning_,
    DEFAULT_BB_KP_TUNING_MINIMUM,
    DEFAULT_BB_KP_TUNING_MAXIMUM);
  gptum::read(
    settings,
    KEY_BB_KI_TUNING,
    this->kiTuning_,
    DEFAULT_BB_KI_TUNING_MINIMUM,
    DEFAULT_BB_KI_TUNING_MAXIMUM);

  /* Evaluation configuration */
  //gptum::read(
  //  settings,
  //  KEY_BB_FACTOR,
  //  factor_,
  //  DEFAULT_BB_FACTOR_PRECISION,
  //  DEFAULT_BB_FACTOR_STEP_SIZE);

  /* Other UI configuration */
  gptum::read(
    settings,
    KEY_BB_SD,
    sd_,
    gptum::make_accuracy(
      gptum::Restriction::Enum::Both,
      gptum::make_range(
        DEFAULT_BB_SD_MINIMUM,
        DEFAULT_BB_SD_MAXIMUM),
      DEFAULT_BB_SD_PRECISION));
  gptum::read(
    settings,
    KEY_BB_CHART,
    chart_,
    gptum::make_accuracy(
      gptum::Restriction::Enum::Both,
      gptum::make_range(
        DEFAULT_BB_CHART_MINIMUM,
        DEFAULT_BB_CHART_MAXIMUM),
      DEFAULT_BB_CHART_PRECISION));

  /* UI configuration group */
  settings->endGroup();

  return settings;
}

QSettings* Ui::write(QSettings* settings) {

  /* Ui configuration group */
  settings->beginGroup(GROUP_UI);

  /* Controller input items */
  gptum::write(settings, KEY_BB_SETPOINT, setpoint_);

  /* Controller output items */
  gptum::write(settings, KEY_BB_TEMPERATURE, temperature_);
  gptum::write(settings, KEY_BB_INTEGRAL, integral_);

  /* PID configuration */
  gptum::write(settings, KEY_BB_KP, kp_);
  gptum::write(settings, KEY_BB_KI, ki_);
  gptum::write(settings, KEY_BB_KD, kd_);

  /* Tuning configuration */
  gptum::write(settings, KEY_BB_KP_TUNING, this->kpTuning_);
  gptum::write(settings, KEY_BB_KI_TUNING, this->kiTuning_);

  /* Evaluation configuration */
  gptum::write(settings, KEY_BB_FACTOR, this->factor_);

  /* Other UI configuration */
  gptum::write(settings, KEY_BB_SD, sd_);
  gptum::write(settings, KEY_BB_CHART, chart_);

  /* UI configuration group */
  settings->endGroup();

  return settings;
}

/* Controller input items */
gptum::Accuracy* Ui::setpoint() { return &setpoint_; }
/* Controller output items */
gptum::Format* Ui::temperature() { return &temperature_; }
gptum::Format* Ui::integral() { return &integral_; }
/* PID configuration */
gptum::Accuracy* Ui::kp() { return &kp_; }
gptum::Accuracy* Ui::ki() { return &ki_; }
gptum::Accuracy* Ui::kd() { return &kd_; }
/* Tuning configuration */
gptum::Range* Ui::kpTuning() { return &kpTuning_; }
gptum::Range* Ui::kiTuning() { return &kiTuning_; }
/* Evaluation configuration */
gptum::Accuracy* Ui::factor() { return &factor_; }
/* Other UI configuration */
gptum::Accuracy* Ui::sd() { return &sd_; }
gptum::Accuracy* Ui::chart() { return &chart_; }

/* Controller input items */
void Ui::setSetpoint(gptum::Accuracy* accuracy) {
  if (accuracy != nullptr) {
    if (setpoint_ != *accuracy) {
      setpoint_ = *accuracy;
      emit setpointChanged();
    }
  }
}
/* Controller output items */
void Ui::setTemperature(gptum::Format* format) {
  if (format != nullptr) {
    if (temperature_ != *format) {
      temperature_ = *format;
      emit temperatureChanged();
    }
  }
}
void Ui::setIntegral(gptum::Format* format) {
  if (format != nullptr) {
    if (integral_ != *format) {
      integral_ = *format;
      emit integralChanged();
    }
  }
}
/* PID configuration */
void Ui::setKp(gptum::Accuracy* accuracy) {
  if (accuracy != nullptr) {
    if (kp_ != *accuracy) {
      kp_ = *accuracy;
      emit kpChanged();
    }
  }
}
void Ui::setKi(gptum::Accuracy* accuracy) {
  if (accuracy != nullptr) {
    if (ki_ != *accuracy) {
      ki_ = *accuracy;
      emit kiChanged();
    }
  }
}
void Ui::setKd(gptum::Accuracy* accuracy) {
  if (accuracy != nullptr) {
    if (kd_ != *accuracy) {
      kd_ = *accuracy;
      emit kdChanged();
    }
  }
}
/* Tuning configuration */
void Ui::setKpTuning(gptum::Range* range) {
  if (range != nullptr) {
    if (kpTuning_ != *range) {
      kpTuning_ = *range;
      emit kpTuningChanged();
    }
  }
}
void Ui::setKiTuning(gptum::Range* range) {
  if (range != nullptr) {
    if (kiTuning_ != *range) {
      kiTuning_ = *range;
      emit kiTuningChanged();
    }
  }
}
/* Evaluation configuration */
void Ui::setFactor(gptum::Accuracy* accuracy) {
  if (accuracy != nullptr) {
    if (factor_ != *accuracy) {
      factor_ = *accuracy;
      emit factorChanged();
    }
  }
}
/* Other UI configuration */
void Ui::setSd(gptum::Accuracy* accuracy) {
  if (accuracy != nullptr) {
    if (sd_ != *accuracy) {
      sd_ = *accuracy;
      emit sdChanged();
    }
  }
}
void Ui::setChart(gptum::Accuracy* accuracy) {
  if (accuracy != nullptr) {
    if (chart_ != *accuracy) {
      chart_ = *accuracy;
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
