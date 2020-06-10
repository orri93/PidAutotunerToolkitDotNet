#include <memory>

#include <QDebug>
#include <QtCore/QObject>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>

#include <gos/pid/toolkit/exception.h>

#include <gos/pid/ui/model/serial.h>
#include <gos/pid/ui/model/interval.h>
#include <gos/pid/ui/model/mode.h>

#include <models.h>

#define GOS_QML_MODELS "ptModels"

namespace gp = ::gos::pid;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuvm = ::gos::pid::toolkit::ui::view::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

namespace models {
typedef std::unique_ptr<gptu::Models> ModelsPointer;
static ModelsPointer _models;
bool create(QQmlContext& context) {

  //_plugin.registerTypes("");
  // qmlRegisterType<gptu::Range>(
  //  GOS_QML_TYPE_RANGE_URI, 1, 0, GOS_QML_TYPE_RANGE_NAME);

  /* Models */
  qmlRegisterUncreatableMetaObject(
    gptum::ptu::Status::staticMetaObject,
    "Pid.Toolkit.Model", 1, 0, "PtStatus",
    "Cannot create namespace PtStatus in QML");
  qmlRegisterUncreatableMetaObject(
    gptum::Force::staticMetaObject,
    "Pid.Toolkit.Model", 1, 0, "Force",
    "Cannot create namespace Force in QML");
  qmlRegisterUncreatableMetaObject(
    gptum::Status::staticMetaObject,
    "Pid.Toolkit.Model", 1, 0, "Status",
    "Cannot create namespace Status in QML");
  qmlRegisterUncreatableMetaObject(
    gptum::tuning::Method::staticMetaObject,
    "Pid.Toolkit.Model.Tuning", 1, 0, "Method",
    "Cannot create namespace Tuning in QML");
  qmlRegisterUncreatableMetaObject(
    gptum::Operation::staticMetaObject,
    "Pid.Toolkit.Model", 1, 0, "Operation",
    "Cannot create namespace Operation in QML");
  qmlRegisterUncreatableMetaObject(
    gptum::Restriction::staticMetaObject,
    "Pid.Toolkit.Model", 1, 0, "Restriction",
    "Cannot create namespace Restriction in QML");

  qmlRegisterUncreatableMetaObject(
    gptum::Serial::staticMetaObject,
    "Pid.Toolkit.Model", 1, 0, "Serial",
    "Cannot create namespace Serial in QML");

  /* View Models */
  qmlRegisterUncreatableMetaObject(
    gptuvm::tuning::Status::staticMetaObject,
    "Pid.Toolkit.Model.Tuning", 1, 0, "Status",
    "Cannot create namespace Tuning Status in QML");
  qmlRegisterUncreatableMetaObject(
    gptuvm::black::box::State::staticMetaObject,
    "Pid.Toolkit.Model.BlackBox", 1, 0, "State",
    "Cannot create namespace BlackBox State in QML");

  /* Models */
  qRegisterMetaType<gptum::ptu::Status::Enum>(
    "::gos::pid::toolkit::ui::model::ptu::Status::Enum");
  qRegisterMetaType<gptum::Force::Enum>(
    "::gos::pid::toolkit::ui::model::Force::Enum");
  qRegisterMetaType<gptum::Status::Enum>(
    "::gos::pid::toolkit::ui::model::Status::Enum");
  qRegisterMetaType<gptum::tuning::Method::Enum>(
    "::gos::pid::toolkit::ui::model::tuning::Method::Enum");
  qRegisterMetaType<gptum::Operation::Enum>(
    "::gos::pid::toolkit::ui::model::Operation::Enum");
  qRegisterMetaType<gptum::Restriction::Enum>(
    "::gos::pid::toolkit::ui::model::Restriction::Enum");

  /* View Models */
  qRegisterMetaType<gptuvm::tuning::Status::Enum>(
    "::gos::pid::toolkit::ui::view::model::tuning::Status::Enum");
  qRegisterMetaType<gptuvm::black::box::State::Enum>(
    "::gos::pid::toolkit::ui::view::model::black::box::State::Enum");

  /* Models */
  qRegisterMetaType<::gos::pid::toolkit::ui::model::Force*>(
    "::gos::pid::toolkit::ui::model::Force*");
  qRegisterMetaType<::gos::pid::toolkit::ui::model::tuning::Method*>(
    "::gos::pid::toolkit::ui::model::tuning::Method*");
  qRegisterMetaType<::gos::pid::toolkit::ui::model::Serial*>(
    "::gos::pid::toolkit::ui::model::Serial*");

  _models = std::make_unique<gptu::Models>();
  if (_models) {
    context.setContextProperty(GOS_QML_MODELS, _models.get());
    if (_models->initialize()) {
      return true;
    } else {
      qCritical() << "Failed to initialize the Models";
    }
  } else {
    qCritical() << "Out of memory when creating the Models";
  }
  return false;
}
Models& instance() {
  if (_models) {
    return *_models;
  } else {
    throw gp::toolkit::exception("The Models instance is undefined");
  }
}
}

Models::Models(QObject* parent) :
  QObject(parent),
  serialBaud_(gptum::Serial::BaudValueRole),
  serialPort_(gptum::Serial::PortValueRole) {
  serialPort_.create();
}

bool Models::initialize() {
  intervalmodel_ = gptum::interval::create();
  modemodel_ = gptum::mode::create();
  return true;
}

const QVariant& Models::interval() const { return intervalmodel_; }
const QVariant& Models::mode() const { return modemodel_; }

/* Models */
gptum::ptu::Status* Models::ptuStatus() { return &ptuStatus_; }
gptum::Force* Models::force() { return &force_; }
gptum::Status* Models::status() { return &status_; }
gptum::tuning::Method* Models::tuningMethod() { return &tuningMethod_; }
gptum::Operation* Models::operation() { return &operation_; }
gptum::Restriction* Models::restriction() { return &restriction_; }
gptum::Serial* Models::serialBaud() { return &serialBaud_; }
gptum::Serial* Models::serialPort() { return &serialPort_; }

/* View Models  */
gptuvm::tuning::Status* Models::tuningStatus() { return &tuningStatus_; }
gptuvm::black::box::State* Models::blackBox() { return &blackBox_; }

gptum::Force& Models::getForce() { return force_; }

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
