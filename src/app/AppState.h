#pragma once

#include <QObject>

class AppState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)

public:
    explicit AppState(QObject* parent = nullptr);

    bool loading() const;
    bool connected() const;
    QString errorMessage() const;

public slots:
    void setLoading(bool loading);
    void setConnected(bool connected);
    void setErrorMessage(const QString& message);

signals:
    void loadingChanged();
    void connectedChanged();
    void errorMessageChanged();

private:
    bool m_loading = false;
    bool m_connected = false;
    QString m_errorMessage;
};
