#include <cstdlib>

#include <memory>
#include <iostream>

#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <orchestration.h>

#define GOS_QM_IMPORT_PATH "pidtoolkitplugin"
#define GOS_QML_MAIN "qrc:/Main.qml"

namespace gptu = ::gos::pid::toolkit::ui;

int main(int argc, char* argv[]) {
  // Qt Charts uses Qt Graphics View Framework for drawing
  // therefore QApplication must be used.
  QApplication application(argc, argv);

  application.setOrganizationName("Geirmundur Orri Sigurdsson");
  application.setOrganizationDomain("fds.is");
  application.setApplicationName("PID Toolkit User Interface");

  QQmlApplicationEngine engine;
  //QObject::connect(
  //  &engine,
  //  &QQmlApplicationEngine::quit,
  //  &application,
  //  &QCoreApplication::quit);
  if (gptu::orchestration::create(application, engine)) {
    const QUrl Url(QStringLiteral(GOS_QML_MAIN));
    QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreated,
      &application,
      [Url](QObject* obj, const QUrl& objUrl) {
        if (!obj && Url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
    engine.load(Url);
    return application.exec();
  }
  return EXIT_FAILURE;
}
