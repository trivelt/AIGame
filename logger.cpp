#include "logger.h"
#include <QDebug>
#include <QTime>

Logger::Logger() {}

void Logger::log(const QString &message)
{
    QDebug debug = qDebug();
    debug.noquote();
    QString messageString = "[" + getCurrentTime() + "] " + message;
    debug << messageString;
}

QString Logger::getCurrentTime()
{
    QTime currentTime = QTime::currentTime();
    QString format = "hh:mm:ss.zzz";
    return currentTime.toString(format);
}

