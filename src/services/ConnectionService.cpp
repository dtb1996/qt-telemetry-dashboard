#include "ConnectionService.h"

ConnectionService::ConnectionService(QObject *parent)
    : QObject(parent)
{
    m_webSocket = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);

    connect(m_webSocket, &QWebSocket::connected, this, &ConnectionService::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &ConnectionService::onDisconnected);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &ConnectionService::onTextMessageReceived);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::errorOccurred), this, &ConnectionService::onError);
}

void ConnectionService::connectToServer(const QUrl &url)
{
    m_webSocket->open(url);
}

void ConnectionService::disconnectFromServer()
{
    m_webSocket->close();
}

bool ConnectionService::isConnected() const
{
    return m_webSocket->state() == QAbstractSocket::ConnectedState;
}

void ConnectionService::sendTextMessage(const QString &message)
{
    if (isConnected())
    {
        m_webSocket->sendTextMessage(message);
    }
}

void ConnectionService::onConnected()
{
    emit connected();
}

void ConnectionService::onDisconnected()
{
    emit disconnected();
}

void ConnectionService::onTextMessageReceived(const QString &message)
{
    emit textMessageReceived(message);
}

void ConnectionService::onError(QAbstractSocket::SocketError error)
{
    const auto err = QString("WebSocket error: %1 (%2)").arg(m_webSocket->errorString()).arg(m_webSocket->state());

    emit errorOccurred(err);
}
