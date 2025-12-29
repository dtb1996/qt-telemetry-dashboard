#include "TelemetryService.h"
#include <QDateTime>

TelemetryService::TelemetryService(TelemetryModel *model, ConnectionService *connection, QObject *parent)
    : QObject(parent)
    , m_model(model)
    , m_connection(connection)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);

    connect(m_timer, &QTimer::timeout, this, &TelemetryService::sendTelemetry);
    connect(m_connection, &ConnectionService::textMessageReceived, this, &TelemetryService::handleMessage);
}

void TelemetryService::start()
{
    m_model->clear();
    m_timer->start();
}

void TelemetryService::stop()
{
    m_timer->stop();
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
    item.status = obj.value("status").toString();
    item.timestamp = QDateTime::fromSecsSinceEpoch(obj.value("timestamp").toInt());

    m_model->addTelemetry(item);
}

void TelemetryService::sendTelemetry()
{
    if (!m_connection->isConnected())
        return;

    // Send a test telemetry payload (echo server)
    QJsonObject payload {
        {"id", "sensor-1"},
        {"type", "temperature"},
        {"value", 72.4},
        {"status", "ok"},
        {"timestamp", QDateTime::currentSecsSinceEpoch()}
    };

    QJsonDocument doc(payload);
    m_connection->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}
