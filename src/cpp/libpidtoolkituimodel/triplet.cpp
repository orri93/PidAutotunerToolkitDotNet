#include <gos/pid/ui/model/triplet.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;

/* PID configuration */
#define KEY_BB_TRIPLET_KP "Kp"
#define KEY_BB_TRIPLET_KI "Ki"
#define KEY_BB_TRIPLET_KD "Kd"
#define DEFAULT_BB_TRIPLET_KP 1.0
#define DEFAULT_BB_TRIPLET_KI 0.01
#define DEFAULT_BB_TRIPLET_KD 0.1

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Triplet::Triplet(QObject* parent) :
  QObject(parent),
  kp_(0.0),
  ki_(0.0),
  kd_(0.0) {
}

Triplet::Triplet(
  const double& kp,
  const double& ki,
  const double& kd,
  QObject* parent) :
  QObject(parent),
  kp_(kp),
  ki_(ki),
  kd_(kd) {
}

Triplet::Triplet(const Triplet& triplet) :
  kp_(triplet.kp_),
  ki_(triplet.ki_),
  kd_(triplet.kd_) {
}

Triplet& Triplet::operator=(const Triplet& triplet) {
  return set(triplet);
}

Triplet& Triplet::set(const Triplet& triplet) {
  if (this != &triplet) {
    kp_ = triplet.kp_;
    ki_ = triplet.ki_;
    kd_ = triplet.kd_;
  }
  return *this;
}

void Triplet::set(const double& kp, const double& ki, const double& kd) {
  setKp(kp);
  setKi(ki);
  setKd(kd);
}


/* Controller tuning items */
const double& Triplet::kp() const { return kp_; }
const double& Triplet::ki() const { return ki_; }
const double& Triplet::kd() const { return kd_; }

bool Triplet::applyKp(const double& kp) {
  if (kp_ != kp) {
    kp_ = kp;
    return true;
  } else {
    return false;
  }
}
bool Triplet::applyKi(const double& ki) {
  if (ki_ != ki) {
    ki_ = ki;
    return true;
  } else {
    return false;
  }
}
bool Triplet::applyKd(const double& kd) {
  if (kd_ != kd) {
    kd_ = kd;
    return true;
  } else {
    return false;
  }
}


void Triplet::setKp(const double& value) {
  if (applyKp(value)) {
    emit kpChanged();
  }
}
void Triplet::setKi(const double& value) {
  if (applyKi(value)) {
    emit kiChanged();
  }
}
void Triplet::setKd(const double& value) {
  if (applyKd(value)) {
    emit kdChanged();
  }
}

Triplet make_triplet(
  const double& kp,
  const double& ki,
  const double& kd) {
  return Triplet(kp, ki, kd);
}

QSettings* read(QSettings* settings, Triplet& triplet) {
  return read(settings, QString(), triplet);
}
QSettings* read(QSettings* settings, const QString& key, Triplet& triplet) {
  Triplet default = make_triplet(
    DEFAULT_BB_TRIPLET_KP,
    DEFAULT_BB_TRIPLET_KI,
    DEFAULT_BB_TRIPLET_KD);
  return read(settings, key, triplet, default);
}
QSettings* read(
  QSettings* settings,
  Triplet& triplet,
  const Triplet& default) {
  return read(settings, QString(), triplet, default);
}
QSettings* read(
  QSettings* settings,
  const QString& key,
  Triplet& triplet,
  const Triplet& default) {
  QVariant value;
  value = settings->value(key + KEY_BB_TRIPLET_KP, default.kp_);
  triplet.setKp(value.toDouble());
  value = settings->value(key + KEY_BB_TRIPLET_KI, default.ki_);
  triplet.setKi(value.toDouble());
  value = settings->value(key + KEY_BB_TRIPLET_KD, default.kd_);
  triplet.setKd(value.toDouble());
  return settings;
}
QSettings* read(
  QSettings* settings,
  Triplet& triplet,
  const double& kp,
  const double& ki,
  const double& kd) {
  return read(settings, QString(), triplet, kp, ki, kd);
}
QSettings* read(
  QSettings* settings,
  const QString& key,
  Triplet& triplet,
  const double& kp,
  const double& ki,
  const double& kd) {
  Triplet default = make_triplet(kp, ki, kd);
  return read(settings, key, triplet, default);
}

QSettings* write(
  QSettings* settings,
  const Triplet& triplet) {
  return write(settings, QString(), triplet);
}

QSettings* write(
  QSettings* settings,
  const QString& key,
  const Triplet& triplet) {
  settings->setValue(key + KEY_BB_TRIPLET_KP, triplet.kp_);
  settings->setValue(key + KEY_BB_TRIPLET_KI, triplet.ki_);
  settings->setValue(key + KEY_BB_TRIPLET_KD, triplet.kd_);
  return settings;
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptum::Triplet& lhs, const gptum::Triplet& rhs) {
  return compare(lhs, rhs) == 0;
}

bool operator!=(const gptum::Triplet& lhs, const gptum::Triplet& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptum::Triplet& first, const gptum::Triplet& second) {
  return (
    first.kp_ == second.kp_ &&
    first.ki_ == second.ki_ &&
    first.kd_ == second.kd_) ? 0 : 1;
}