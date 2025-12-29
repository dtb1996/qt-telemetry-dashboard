#pragma once

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include "src/models/TelemetryModel.h"
#include "ConnectionService.h"

class TelemetryService : public QObject
{
    Q_OBJECT

public:
    explicit TelemetryService(TelemetryModel* model, ConnectionService* connection, QObject* parent = nullptr);

    void start();
    void stop();

private slots:
    void handleMessage(const QString& message);

private:
    TelemetryModel* m_model;
    ConnectionService* m_connection;
};
