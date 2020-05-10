#include <blackbox.h>

/* Black Box configuration group */
#define GROUP_BLACK_BOX "BlackBox"

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
#define KEY_BB_KP_RANGE_MIN "KpRangeMinimum"
#define KEY_BB_KP_RANGE_MAX "KpRangeMaximum"
#define KEY_BB_KI_RANGE_MIN "KiRangeMinimum"
#define KEY_BB_KI_RANGE_MAX "KiRangeMaximum"
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

/* Other configuration */
#define KEY_BB_WINDOW_SIZE "WindowSize"
#define KEY_BB_STANDARD_DEVIATION "StandardDeviation"
#define DEFAULT_BB_WINDOW_SIZE 15
#define DEFAULT_BB_STANDARD_DEVIATION 0.125

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

BlackBox::BlackBox(QObject* parent) :
  ::gos::pid::toolkit::ui::configuration::Base(parent),
  kp_(0.0),
  ki_(0.0),
  kd_(0.0),
  base_(0.0),
  isBase_(false),
  setpoint_(0.0),
  manual_(0),
  stableDuration_(0),
  internalVariables_(false),
  windowSize_(0),
  sd_(0.0) {
}

BlackBox::BlackBox(const BlackBox& blackBox) :
  kp_(blackBox.kp_),
  ki_(blackBox.ki_),
  kd_(blackBox.kd_),
  kpRange_(blackBox.kpRange_),
  kiRange_(blackBox.kiRange_),
  base_(blackBox.base_),
  isBase_(blackBox.isBase_),
  setpoint_(blackBox.setpoint_),
  manual_(blackBox.manual_),
  stableDuration_(blackBox.stableDuration_),
  internalVariables_(blackBox.internalVariables_),
  separator_(blackBox.separator_),
  file_(blackBox.file_),
  tuningFile_(blackBox.tuningFile_),
  windowSize_(blackBox.windowSize_),
  sd_(blackBox.sd_) {
}

BlackBox& BlackBox::operator=(const BlackBox& blackBox) {
  if (this != &blackBox) {
    kp_ = blackBox.kp_;
    ki_ = blackBox.ki_;
    kd_ = blackBox.kd_;
    kpRange_ = blackBox.kpRange_;
    kiRange_ = blackBox.kiRange_;
    base_ = blackBox.base_;
    isBase_ = blackBox.isBase_;
    setpoint_ = blackBox.setpoint_;
    manual_ = blackBox.manual_;
    stableDuration_ = blackBox.stableDuration_;
    internalVariables_ = blackBox.internalVariables_;
    separator_ = blackBox.separator_;
    file_ = blackBox.file_;
    tuningFile_ = blackBox.tuningFile_;
    windowSize_ = blackBox.windowSize_;
    sd_ = blackBox.sd_;
  }
  return *this;
}

QSettings* BlackBox::read(QSettings* settings) {
  QVariant value, minimum, maximum;

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
  minimum = settings->value(KEY_BB_KP_RANGE_MIN, DEFAULT_BB_KP_RANGE_MIN);
  maximum = settings->value(KEY_BB_KP_RANGE_MAX, DEFAULT_BB_KP_RANGE_MAX);
  setKpRange(minimum.toFloat(), maximum.toFloat());
  minimum = settings->value(KEY_BB_KI_RANGE_MIN, DEFAULT_BB_KI_RANGE_MIN);
  maximum = settings->value(KEY_BB_KI_RANGE_MAX, DEFAULT_BB_KI_RANGE_MAX);
  setKiRange(minimum.toFloat(), maximum.toFloat());

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
  settings->setValue(KEY_BB_KP_RANGE_MIN, kpRange_.minimum());
  settings->setValue(KEY_BB_KP_RANGE_MAX, kpRange_.maximum());
  settings->setValue(KEY_BB_KI_RANGE_MIN, kiRange_.minimum());
  settings->setValue(KEY_BB_KI_RANGE_MAX, kiRange_.maximum());

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

  return settings;
}


/* PID configuration */
const double& BlackBox::kp() const { return kp_; }
const double& BlackBox::ki() const { return ki_; }
const double& BlackBox::kd() const { return kd_; }

/* Tuning configuration */
gptu::Range* BlackBox::kpRange() { return &kpRange_; }
gptu::Range* BlackBox::kiRange() { return &kiRange_; }

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
void BlackBox::setKpRange(gptu::Range* value) {
  if (value != nullptr) {
    if (kpRange_ != *value) {
      kpRange_ = *value;
      emit kpRangeChanged();
    }
  }
}
void BlackBox::setKiRange(gptu::Range* value) {
  if (value != nullptr) {
    if (kiRange_ != *value) {
      kiRange_ = *value;
      emit kiRangeChanged();
    }
  }
}
void BlackBox::setKpRange(const double& minimum, const double& maximum) {
  if (kpRange_.minimum() != minimum || kpRange_.maximum() != maximum) {
    kpRange_.set(minimum, maximum);
    emit kpRangeChanged();
  }
}
void BlackBox::setKiRange(const double& minimum, const double& maximum) {
  if (kiRange_.minimum() != minimum || kiRange_.maximum() != maximum) {
    kiRange_.set(minimum, maximum);
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
  return (first.kp_ == second.kp_ &&
    first.ki_ == second.ki_ &&
    first.kd_ == second.kd_ &&
    first.kpRange_ == second.kpRange_ &&
    first.kiRange_ == second.kiRange_ &&
    first.base_ == second.base_ &&
    first.isBase_ == second.isBase_ &&
    first.setpoint_ == second.setpoint_ &&
    first.manual_ == second.manual_ &&
    first.stableDuration_ == second.stableDuration_ &&
    first.internalVariables_ == second.internalVariables_ &&
    first.separator_ == second.separator_ &&
    first.file_ == second.file_ &&
    first.tuningFile_ == second.tuningFile_ &&
    first.windowSize_ == second.windowSize_ &&
    first.sd_ == second.sd_) ? 0 : 1;
}