#ifndef LOGGER_H
#define LOGGER_H
#include <QString>
#include <QDebug>

class Logger
{
public:
    Logger();
    static void log(const QString& message);

private:
    static QString getCurrentTime();
};

#endif // LOGGER_H
