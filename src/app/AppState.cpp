#include "AppState.h"

AppState::AppState(QObject *parent)
    : QObject(parent)
{
    
}

bool AppState::loading() const
{
    return m_loading;
}

bool AppState::connected() const
{
    return m_connected;
}

QString AppState::errorMessage() const
{
    return m_errorMessage;
}

void AppState::setLoading(bool loading)
{
    if (m_loading == loading)
        return;

    m_loading = loading;
    emit loadingChanged();
}

void AppState::setConnected(bool connected)
{
    if (m_connected == connected)
        return;

    m_connected = connected;
    emit connectedChanged();
}

void AppState::setErrorMessage(const QString &message)
{
    if (m_errorMessage == message)
        return;

    m_errorMessage = message;
    emit errorMessageChanged();
}
