#include "utils.h"
#include <QTimer>
#include <QEventLoop>

void Utils::sleep(int msec)
{
    QEventLoop loop;
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(msec);
    loop.exec();
}
