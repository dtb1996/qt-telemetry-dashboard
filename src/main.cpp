#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "app/AppController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto controller = new AppController();
    QQmlEngine::setObjectOwnership(controller, QQmlEngine::CppOwnership);
    qmlRegisterSingletonInstance("QtTelemetry", 1, 0, "AppController", controller);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QtTelemetryDashboard", "Main");

    return app.exec();
}
