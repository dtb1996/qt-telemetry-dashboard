#pragma once

#include <QString>
#include <QDateTime>

struct TelemetryItem
{
    QString id;
    QDateTime timestamp;
    QString type;
    double value;
    QString status;
};
