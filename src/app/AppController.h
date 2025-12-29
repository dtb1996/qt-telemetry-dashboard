#pragma once

#include <QObject>
#include "AppState.h"
#include "src/models/TelemetryModel.h"
#include "src/services/ConnectionService.h"
#include "src/services/TelemetryService.h"

class AppController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(AppState* appState READ appState CONSTANT)
    Q_PROPERTY(TelemetryModel* telemetryModel READ telemetryModel CONSTANT)

public:
    explicit AppController(QObject* parent = nullptr);

    AppState* appState() const;
    TelemetryModel* telemetryModel() const;

    Q_INVOKABLE void connectToServer(const QString& url);
    Q_INVOKABLE void disconnect();

private:
    AppState* m_appState;
    TelemetryModel* m_model;
    ConnectionService* m_connectionService;
    TelemetryService* m_telemetryService;
};
