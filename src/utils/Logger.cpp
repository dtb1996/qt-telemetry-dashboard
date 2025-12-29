#include "Logger.h"
#include <QDebug>

void Logger::log(Level level, const QString &message)
{
    switch (level)
    {
    case Level::Debug:
        qDebug() << message;
        break;
    case Level::Info:
        qInfo() << message;
        break;
    case Level::Warning:
        qWarning() << message;
        break;
    case Level::Error:
        qCritical() << message;
        break;
    }
}
