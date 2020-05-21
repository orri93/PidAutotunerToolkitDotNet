#include <blackbox.h>

/* Black Box configuration group */
#define GROUP_BLACK_BOX "BlackBox"

#define GROUP_EVALUATION "Evaluation"

/* PID configuration */
#define KEY_BB_KP "Kp"
#define KEY_BB_KI "Ki"
#define KEY_BB_KD "Kd"
#define DEFAULT_BB_KP 0.01
#define DEFAULT_BB_KI 0.01
#define DEFAULT_BB_KD 0.01

/* Controller configuration */
#define KEY_BB_BASE "Base"
#define KEY_BB_IS_BASE "UseBase"
#define KEY_BB_SETPOINT "setpoint"
#define KEY_BB_MANUAL "Manual"
#define DEFAULT_BB_BASE 30.0
#define DEFAULT_BB_IS_BASE false
#define DEFAULT_BB_SETPOINT 100.0
#define DEFAULT_BB_MANUAL 0

/* Tuning configuration */
#define KEY_BB_KP_RANGE "KpRange"
#define KEY_BB_KI_RANGE "KiRange"
#define DEFAULT_BB_KP_RANGE_MIN 0.0
#define DEFAULT_BB_KP_RANGE_MAX 10.0
#define DEFAULT_BB_KI_RANGE_MIN 0.0
#define DEFAULT_BB_KI_RANGE_MAX 0.1

/* Timers configuration */
#define KEY_BB_STABLE_DURATION "StableDurationMin"
#define DEFAULT_BB_STABLE_DURATION 15

/* Logging configuration */
#define KEY_BB_LOG_INTERNAL_VARIABLES "LoggingInternalVariables"
#define KEY_BB_LOG_SEPARATOR "LoggingSeparator"
#define KEY_BB_LOG_FILE "LoggingFile"
#define KEY_BB_LOG_TUNING_FILE "LoggingTuningFile"
#define DEFAULT_BB_LOG_INTERNAL_VARIABLES false
#define DEFAULT_BB_LOG_SEPARATOR ","
#define DEFAULT_BB_LOG_FILE "tuning.csv"
#define DEFAULT_BB_LOG_TUNING_FILE "blackbox.csv"

  /* Evaluation configuration */
#define KEY_BB_FACTOR_TARGET_TIME_FACTOR "TargetTime"
#define KEY_BB_FACTOR_INTEGRAL_BUILDUP "IntegralBuildup"
#define KEY_BB_FACTOR_PEAK_ERROR "PeakError"
#define KEY_BB_FACTOR_STABLE "Stable"

/* Other configuration */
#define KEY_BB_WINDOW_SIZE "WindowSize"
#define KEY_BB_STANDARD_DEVIATION "StandardDeviation"
#define DEFAULT_BB_WINDOW_SIZE 15
#define DEFAULT_BB_STANDARD_DEVIATION 0.125

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

BlackBox::BlackBox(QObject* parent) :
  gptum::Ptu(parent),
  /* PID configuration */
  kp_(0.0),
  ki_(0.0),
  kd_(0.0),
  /* Controller configuration  */
  base_(0.0),
  isBase_(false),
  setpoint_(0.0),
  manual_(0),
  /* Timers configuration */
  stableDuration_(0),
  /* Logging configuration */
  internalVariables_(false),
  /* Evaluation configuration */
  /* Other configuration */
  windowSize_(0),
  sd_(0.0) {
}

BlackBox::BlackBox(const BlackBox& blackBox) :
  /* PID configuration */
  kp_(blackBox.kp_),
  ki_(blackBox.ki_),
  kd_(blackBox.kd_),
  /* Tuning configuration */
  kpRange_(blackBox.kpRange_),
  kiRange_(blackBox.kiRange_),
  /* Controller configuration  */
  base_(blackBox.base_),
  isBase_(blackBox.isBase_),
  setpoint_(blackBox.setpoint_),
  manual_(blackBox.manual_),
  /* Timers configuration */
  stableDuration_(blackBox.stableDuration_),
  /* Logging configuration */
  internalVariables_(blackBox.internalVariables_),
  separator_(blackBox.separator_),
  file_(blackBox.file_),
  tuningFile_(blackBox.tuningFile_),
  /* Evaluation configuration */
  targetTimeFactor_(blackBox.targetTimeFactor_),
  integralBuildupFactor_(blackBox.integralBuildupFactor_),
  peakErrorFactor_(blackBox.peakErrorFactor_),
  stableFactor_(blackBox.stableFactor_),
  /* Other configuration */
  windowSize_(blackBox.windowSize_),
  sd_(blackBox.sd_) {
}

BlackBox& BlackBox::operator=(const BlackBox& blackBox) {
  if (this != &blackBox) {
    /* PID configuration */
    kp_ = blackBox.kp_;
    ki_ = blackBox.ki_;
    kd_ = blackBox.kd_;
    /* Tuning configuration */
    kpRange_ = blackBox.kpRange_;
    kiRange_ = blackBox.kiRange_;
    /* Controller configuration  */
    base_ = blackBox.base_;
    isBase_ = blackBox.isBase_;
    setpoint_ = blackBox.setpoint_;
    manual_ = blackBox.manual_;
    /* Timers configuration */
    stableDuration_ = blackBox.stableDuration_;
    /* Logging configuration */
    internalVariables_ = blackBox.internalVariables_;
    separator_ = blackBox.separator_;
    file_ = blackBox.file_;
    tuningFile_ = blackBox.tuningFile_;
    /* Evaluation configuration */
    targetTimeFactor_ = blackBox.targetTimeFactor_;
    integralBuildupFactor_ = blackBox.integralBuildupFactor_;
    peakErrorFactor_ = blackBox.peakErrorFactor_;
    stableFactor_ = blackBox.stableFactor_;
    /* Other configuration */
    windowSize_ = blackBox.windowSize_;
    sd_ = blackBox.sd_;
  }
  return *this;
}

QSettings* BlackBox::read(QSettings* settings) {
  QVariant value;

  /* Black Box configuration group */
  settings->beginGroup(GROUP_BLACK_BOX);

  /* PID configuration */
  value = settings->value(KEY_BB_KP, DEFAULT_BB_KP);
  setKp(value.toFloat());
  value = settings->value(KEY_BB_KI, DEFAULT_BB_KI);
  setKi(value.toFloat());
  value = settings->value(KEY_BB_KD, DEFAULT_BB_KD);
  setKd(value.toFloat());

  /* Tuning configuration */
  gptum::read(
    settings,
    KEY_BB_KP_RANGE,
    this->kpRange_,
    DEFAULT_BB_KP_RANGE_MIN,
    DEFAULT_BB_KP_RANGE_MAX);
  gptum::read(
    settings,
    KEY_BB_KI_RANGE,
    this->kiRange_,
    DEFAULT_BB_KI_RANGE_MIN,
    DEFAULT_BB_KI_RANGE_MAX);

  /* Controller configuration  */
  value = settings->value(KEY_BB_BASE, DEFAULT_BB_BASE);
  setBase(value.toFloat());
  value = settings->value(KEY_BB_IS_BASE, DEFAULT_BB_IS_BASE);
  setIsBase(value.toBool());
  value = settings->value(KEY_BB_SETPOINT, DEFAULT_BB_SETPOINT);
  setSetpoint(value.toFloat());
  value = settings->value(KEY_BB_MANUAL, DEFAULT_BB_MANUAL);
  setManual(value.toUInt());

  /* Timers configuration */
  value = settings->value(KEY_BB_STABLE_DURATION, DEFAULT_BB_STABLE_DURATION);
  setStableDuration(value.toInt());

  /* Logging configuration */
  value = settings->value(
    KEY_BB_LOG_INTERNAL_VARIABLES,
    DEFAULT_BB_LOG_INTERNAL_VARIABLES);
  setInternalVariables(value.toBool());
  value = settings->value(KEY_BB_LOG_SEPARATOR, DEFAULT_BB_LOG_SEPARATOR);
  setSeparator(value.toString());
  value = settings->value(KEY_BB_LOG_FILE, DEFAULT_BB_LOG_FILE);
  setFile(value.toString());
  value = settings->value(KEY_BB_LOG_TUNING_FILE, DEFAULT_BB_LOG_TUNING_FILE);
  setTuningFile(value.toString());

  /* Other configuration */
  value = settings->value(KEY_BB_WINDOW_SIZE, DEFAULT_BB_WINDOW_SIZE);
  setWindowSize(value.toInt());
  value = settings->value(
    KEY_BB_STANDARD_DEVIATION,
    DEFAULT_BB_STANDARD_DEVIATION);
  setSd(value.toFloat());

  /* Black Box configuration group */
  settings->endGroup();

  /* Evaluation configuration */
  settings->beginGroup(GROUP_EVALUATION);
  gptum::read(settings, KEY_BB_FACTOR_TARGET_TIME_FACTOR, targetTimeFactor_);
  gptum::read(settings, KEY_BB_FACTOR_INTEGRAL_BUILDUP, integralBuildupFactor_);
  gptum::read(settings, KEY_BB_FACTOR_PEAK_ERROR, peakErrorFactor_);
  gptum::read(settings, KEY_BB_FACTOR_STABLE, stableFactor_);
  settings->endGroup();

  return settings;
}
QSettings* BlackBox::write(QSettings* settings) {

  /* Black Box configuration group */
  settings->beginGroup(GROUP_BLACK_BOX);

  /* PID configuration */
  settings->setValue(KEY_BB_KP, kp_);
  settings->setValue(KEY_BB_KI, ki_);
  settings->setValue(KEY_BB_KD, kd_);

  /* Tuning configuration */
  gptum::write(settings, KEY_BB_KP_RANGE, this->kpRange_);
  gptum::write(settings, KEY_BB_KI_RANGE, this->kiRange_);

  /* Controller configuration  */
  settings->setValue(KEY_BB_BASE, base_);
  settings->setValue(KEY_BB_IS_BASE, isBase_);
  settings->setValue(KEY_BB_SETPOINT, setpoint_);
  settings->setValue(KEY_BB_MANUAL, manual_);

  /* Timers configuration */
  settings->setValue(KEY_BB_STABLE_DURATION, stableDuration_);

  /* Logging configuration */
  settings->setValue(KEY_BB_LOG_INTERNAL_VARIABLES, internalVariables_);
  settings->setValue(KEY_BB_LOG_SEPARATOR, separator_);
  settings->setValue(KEY_BB_LOG_FILE, file_);
  settings->setValue(KEY_BB_LOG_TUNING_FILE, tuningFile_);

  /* Other configuration */
  settings->setValue(KEY_BB_WINDOW_SIZE, windowSize_);
  settings->setValue(KEY_BB_STANDARD_DEVIATION, sd_);

  /* Black Box configuration group */
  settings->endGroup();

  /* Evaluation configuration */
  settings->beginGroup(GROUP_EVALUATION);
  gptum::write(settings, KEY_BB_FACTOR_TARGET_TIME_FACTOR, targetTimeFactor_);
  gptum::write(settings, KEY_BB_FACTOR_INTEGRAL_BUILDUP, integralBuildupFactor_);
  gptum::write(settings, KEY_BB_FACTOR_PEAK_ERROR, peakErrorFactor_);
  gptum::write(settings, KEY_BB_FACTOR_STABLE, stableFactor_);
  settings->endGroup();

  return settings;
}


/* PID configuration */
const double& BlackBox::kp() const { return kp_; }
const double& BlackBox::ki() const { return ki_; }
const double& BlackBox::kd() const { return kd_; }

/* Tuning configuration */
gptum::Range* BlackBox::kpRange() { return &kpRange_; }
gptum::Range* BlackBox::kiRange() { return &kiRange_; }

/* Controller configuration  */
const double& BlackBox::base() const { return base_; }
const bool& BlackBox::isBase() const { return isBase_; }
const double& BlackBox::setpoint() const { return setpoint_; }
const quint16& BlackBox::manual() const { return manual_; }

/* Timers configuration */
const int& BlackBox::stableDuration() const { return stableDuration_; }

/* Logging configuration */
const bool& BlackBox::internalVariables() const { return internalVariables_; }
const QString& BlackBox::separator() const { return separator_; }
const QString& BlackBox::file() const { return file_; }
const QString& BlackBox::tuningFile() const { return tuningFile_; }

/* Evaluation configuration */
gptum::Factor* BlackBox::targetTimeFactor() {
  return &targetTimeFactor_;
}
gptum::Factor* BlackBox::integralBuildupFactor() {
  return &integralBuildupFactor_;
}
gptum::Factor* BlackBox::peakErrorFactor() {
  return &peakErrorFactor_;
}
gptum::Factor* BlackBox::stableFactor() {
  return &stableFactor_;
}

/* Other configuration */
const int& BlackBox::windowSize() const { return windowSize_; }
const double& BlackBox::sd() const { return sd_; }

/* PID configuration */
void BlackBox::setKp(const double& value) {
  if (kp_ != value) {
    kp_ = value;
    emit kpChanged();
  }
}
void BlackBox::setKi(const double& value) {
  if (ki_ != value) {
    ki_ = value;
    emit kiChanged();
  }
}
void BlackBox::setKd(const double& value) {
  if (kd_ != value) {
    kd_ = value;
    emit kdChanged();
  }
}

/* Tuning configuration */
void BlackBox::setKpRange(gptum::Range* value) {
  if (value != nullptr) {
    if (kpRange_ != *value) {
      kpRange_ = *value;
      emit kpRangeChanged();
    }
  }
}
void BlackBox::setKiRange(gptum::Range* value) {
  if (value != nullptr) {
    if (kiRange_ != *value) {
      kiRange_ = *value;
      emit kiRangeChanged();
    }
  }
}
void BlackBox::setKpRange(const double& from, const double& to) {
  if (kpRange_.from() != from || kpRange_.to() != to) {
    kpRange_.set(from, to);
    emit kpRangeChanged();
  }
}
void BlackBox::setKiRange(const double& from, const double& to) {
  if (kiRange_.from() != from || kiRange_.to() != to) {
    kiRange_.set(from, to);
    emit kiRangeChanged();
  }
}

/* Controller configuration  */
void BlackBox::setBase(const double& value) {
  if (base_ != value) {
    base_ = value;
    emit baseChanged();
  }
}
void BlackBox::setIsBase(const bool& value) {
  if (isBase_ != value) {
    isBase_ = value;
    emit isBaseChanged();
  }
}
void BlackBox::setSetpoint(const double& value) {
  if (setpoint_ != value) {
    setpoint_ = value;
    emit setpointChanged();
  }
}
void BlackBox::setManual(const quint16& value) {
  if (manual_ != value) {
    manual_ = value;
    emit setpointChanged();
  }
}

/* Timers configuration */
void BlackBox::setStableDuration(const int& value) {
  if (stableDuration_ != value) {
    stableDuration_ = value;
    emit stableDurationChanged();
  }
}

/* Logging configuration */
void BlackBox::setInternalVariables(const bool& value) {
  if (internalVariables_ != value) {
    internalVariables_ = value;
    emit internalVariablesChanged();
  }
}
void BlackBox::setSeparator(const QString& value) {
  if (separator_ != value) {
    separator_ = value;
    emit separatorChanged();
  }
}
void BlackBox::setFile(const QString& value) {
  if (file_ != value) {
    file_ = value;
    emit fileChanged();
  }
}
void BlackBox::setTuningFile(const QString& value) {
  if (tuningFile_ != value) {
    tuningFile_ = value;
    emit tuningFileChanged();
  }
}

/* Evaluation configuration */
void BlackBox::setTargetTimeFactor(gptum::Factor* value) {
  if (value != nullptr && compare(targetTimeFactor_, *value) != 0) {
    targetTimeFactor_.set(*value);
    emit targetTimeFactorChanged();
  }
}
void BlackBox::setIntegralBuildupFactor(gptum::Factor* value) {
  if (value != nullptr && compare(integralBuildupFactor_, *value) != 0) {
    integralBuildupFactor_.set(*value);
    emit integralBuildupFactorChanged();
  }
}
void BlackBox::setPeakErrorFactor(gptum::Factor* value) {
  if (value != nullptr && compare(peakErrorFactor_, *value) != 0) {
    peakErrorFactor_.set(*value);
    emit peakErrorFactorChanged();
  }
}
void BlackBox::setStableFactor(gptum::Factor* value) {
  if (value != nullptr && compare(stableFactor_, *value) != 0) {
    stableFactor_.set(*value);
    emit stableFactorChanged();
  }
}

/* Other configuration */
void BlackBox::setWindowSize(const int& value) {
  if (windowSize_ != value) {
    windowSize_ = value;
    emit windowSizeChanged();
  }
}
void BlackBox::setSd(const double& value) {
  if (sd_ != value) {
    sd_ = value;
    emit sdChanged();
  }
}

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptuc::BlackBox& lhs, const gptuc::BlackBox& rhs) {
  return compare(lhs, rhs) == 0;
}
bool operator!=(const gptuc::BlackBox& lhs, const gptuc::BlackBox& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptuc::BlackBox& first, const gptuc::BlackBox& second) {
  return (
    /* PID configuration */
    first.kp_ == second.kp_ &&
    first.ki_ == second.ki_ &&
    first.kd_ == second.kd_ &&
    /* Tuning configuration */
    first.kpRange_ == second.kpRange_ &&
    first.kiRange_ == second.kiRange_ &&
    /* Controller configuration  */
    first.base_ == second.base_ &&
    first.isBase_ == second.isBase_ &&
    first.setpoint_ == second.setpoint_ &&
    first.manual_ == second.manual_ &&
    /* Timers configuration */
    first.stableDuration_ == second.stableDuration_ &&
    /* Logging configuration */
    first.internalVariables_ == second.internalVariables_ &&
    first.separator_ == second.separator_ &&
    first.file_ == second.file_ &&
    first.tuningFile_ == second.tuningFile_ &&
    /* Evaluation configuration */
    first.targetTimeFactor_ == second.targetTimeFactor_ &&
    first.integralBuildupFactor_ == second.integralBuildupFactor_ &&
    first.peakErrorFactor_ == second.peakErrorFactor_ &&
    first.stableFactor_ == second.stableFactor_ &&
    /* Other configuration */
    first.windowSize_ == second.windowSize_ &&
    first.sd_ == second.sd_) ? 0 : 1;
}