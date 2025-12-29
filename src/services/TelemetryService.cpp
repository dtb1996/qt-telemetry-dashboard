#include "TelemetryService.h"
#include <QDateTime>

TelemetryService::TelemetryService(TelemetryModel *model, ConnectionService *connection, QObject *parent)
    : QObject(parent)
    , m_model(model)
    , m_connection(connection)
{
    connect(m_connection, &ConnectionService::textMessageReceived, this, &TelemetryService::handleMessage);
}

void TelemetryService::start()
{
    m_model->clear();
}

void TelemetryService::stop()
{
    m_model->clear();
}

void TelemetryService::handleMessage(const QString &message)
{
    const auto doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject())
        return;

    const auto obj = doc.object();

    TelemetryItem item;
    item.id = obj.value("id").toString();
    item.type = obj.value("type").toString();
    item.value = obj.value("value").toDouble();
    item.status = obj.value("id").toString();
    item.timestamp = QDateTime::fromSecsSinceEpoch(obj.value("timestamp").toInt());

    m_model->addTelemetry(item);
}
