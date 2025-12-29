#pragma once

#include <QString>

class Logger
{
public:
    enum class Level
    {
        Debug,
        Info,
        Warning,
        Error
    };

    static void log(Level level, const QString& message);
};
