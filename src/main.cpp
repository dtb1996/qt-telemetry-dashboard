#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "app/AppController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<AppController>(
        "QtTelemetry",
        1, 0,
        "AppController",
        [](QQmlEngine*, QJSEngine*) -> QObject* {
            return new AppController();
        }
    );

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
