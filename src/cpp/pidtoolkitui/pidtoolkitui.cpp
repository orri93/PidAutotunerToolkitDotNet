#include <cstdlib>

#include <memory>
#include <iostream>

#include <QtWidgets/QApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtCore/QDir>

#include <gos/pid/ui/fvalidator.h>

#include <orchestration.h>

#define GOS_QML_ORCHESTRATION "orchestration"
#define GOS_QML_FLOAT_VALIDATOR "FloatValidator"

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;

namespace registration {
bool items();
}

namespace orchestration {
typedef std::unique_ptr<gptu::Orchestration> OrchestrationPointer;
static OrchestrationPointer orchestration_;
bool create(QQuickView& viewer);
}

int main(int argc, char* argv[]) {
  // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
  QApplication app(argc, argv);

  QQuickView viewer;

  // The following are needed to make examples run without having to install the module
  // in desktop environments.
#ifdef Q_OS_WIN
  QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
  QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
  viewer.engine()->addImportPath(
    extraImportPath.arg(
      QGuiApplication::applicationDirPath(),
      QString::fromLatin1("qml"))
  );

  registration::items();

  viewer.setTitle(QStringLiteral("PID HMI"));

  QObject::connect(
    viewer.engine(),
    &QQmlEngine::quit,
    &viewer,
    &QWindow::close);

  viewer.setSource(QUrl("qrc:/qml/pid/main.qml"));
  viewer.setResizeMode(QQuickView::SizeRootObjectToView);
  viewer.setColor(QColor("#404040"));
  if (orchestration::create(viewer)) {
    viewer.show();
    return app.exec();
  } else {
    return EXIT_FAILURE;
  }
}

namespace registration {
bool items() {
#ifdef GOS_QML_NOT_USE_ANONYMOUS_REGISTRATION
  qmlRegisterType<gptu::FloatValidator>(
    GOS_QML_FLOAT_VALIDATOR,
    1
    0,
    GOS_QML_FLOAT_VALIDATOR);
#else
  qmlRegisterAnonymousType<gptu::FloatValidator>(GOS_QML_FLOAT_VALIDATOR, 1);
#endif
}
}

namespace orchestration {
bool create(QQuickView& viewer) {
  orchestration_ = std::make_unique<gptu::Orchestration>(viewer);
  if (orchestration_) {
    viewer.rootContext()->setContextProperty(
      GOS_QML_ORCHESTRATION,
      orchestration_.get());
    if (orchestration_->initialize()) {
      return true;
    } else {
      std::cerr << "Failed to initialize the Orchestration" << std::endl;
      return false;
    }
  } else {
    std::cerr << "Out of memory when creating the Orchestration" << std::endl;
    return false;
  }
}
}
