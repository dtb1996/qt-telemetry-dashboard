#include "AppController.h"
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

AppController::AppController(QObject *parent)
    : QObject(parent)
{
    m_appState = new AppState(this);
    m_model = new TelemetryModel(this);
    m_connectionService = new ConnectionService(this);
    m_telemetryService = new TelemetryService(m_model, m_connectionService, this);

    connect(m_connectionService, &ConnectionService::connected, this, [this]() {
        m_appState->setLoading(false);
        m_appState->setConnected(true);
        m_appState->setErrorMessage({});
        m_telemetryService->start();
    });

    connect(m_connectionService, &ConnectionService::disconnected, this, [this]() {
        m_appState->setConnected(false);
        m_telemetryService->stop();
    });

    connect(m_connectionService, &ConnectionService::errorOccurred, this, [this](const QString& error) {
        m_appState->setLoading(false);
        m_appState->setConnected(false);
        m_appState->setErrorMessage(error);
    });
}

AppState *AppController::appState() const
{
    return m_appState;
}

TelemetryModel *AppController::telemetryModel() const
{
    return m_model;
}

void AppController::connectToServer(const QString &url)
{
    m_appState->setLoading(true);
    m_connectionService->connectToServer(QUrl(url));

    // Send a test telemetry payload (echo server)
    QJsonObject payload {
        {"id", "sensor-1"},
        {"type", "temperature"},
        {"value", 72.4},
        {"status", "ok"},
        {"timestamp", QDateTime::currentSecsSinceEpoch()}
    };

    QJsonDocument doc(payload);
    m_connectionService->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

void AppController::disconnect()
{
    m_connectionService->disconnectFromServer();
}
