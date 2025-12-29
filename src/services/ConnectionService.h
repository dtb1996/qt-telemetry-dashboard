#pragma once

#include <QObject>
#include <QWebSocket>
#include <QUrl>

class ConnectionService : public QObject {
    Q_OBJECT

public:
    explicit ConnectionService(QObject* parent = nullptr);

    void connectToServer(const QUrl& url);
    void disconnectFromServer();
    bool isConnected() const;

    void sendTextMessage(const QString& message);

signals:
    void connected();
    void disconnected();
    void textMessageReceived(const QString& message);
    void errorOccurred(const QString& error);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString& message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket* m_webSocket;
};
