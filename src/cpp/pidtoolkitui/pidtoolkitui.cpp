#include <cstdlib>

#include <memory>
#include <iostream>

#include <QtWidgets/QApplication>
#ifdef GOS_QML_USE_QUICK_VIEW
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtCore/QDir>
#else
#include <QQmlApplicationEngine>
#endif
#include <QtQml/QQmlContext>

#include <orchestration.h>

#define GOS_QM_IMPORT_PATH "pidtoolkitplugin"
#define GOS_QML_MAIN "qrc:/main.qml"

namespace gptu = ::gos::pid::toolkit::ui;

int main(int argc, char* argv[]) {
  // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
  QApplication app(argc, argv);

#ifdef GOS_QML_USE_QUICK_VIEW
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
  viewer.setTitle(QStringLiteral("PID HMI"));
  QObject::connect(
    viewer.engine(),
    &QQmlEngine::quit,
    &viewer,
    &QWindow::close);
  QQmlContext* context = viewer.rootContext();
  if (context != nullptr) {
    if (orchestration::create(*context)) {
      viewer.setSource(QUrl(GOS_QML_MAIN));
      viewer.setResizeMode(QQuickView::SizeRootObjectToView);
      viewer.setColor(QColor("#404040"));
      viewer.show();
      return app.exec();
    }
  }
  return EXIT_FAILURE;
#else
  QQmlApplicationEngine engine;
  //engine.addImportPath(GOS_QM_IMPORT_PATH);
  QQmlContext* context = engine.rootContext();
  if (context != nullptr) {
    if (gptu::orchestration::create(*context)) {
      const QUrl Url(QStringLiteral(GOS_QML_MAIN));
      QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [Url](QObject* obj, const QUrl& objUrl) {
          if (!obj && Url == objUrl)
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
      engine.load(Url);
      return app.exec();
    }
  } else {
    std::cerr << "The QML Root Context is undefined";
  }
  return EXIT_FAILURE;
#endif
}
