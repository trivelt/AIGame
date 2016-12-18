#include "utils.h"
#include <QTimer>
#include <QEventLoop>
#include <cstdlib>
#include <ctime>

void Utils::sleep(int msec)
{
    QEventLoop loop;
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(msec);
    loop.exec();
}

void Utils::initRandoms()
{
    srand( time( NULL ) );
}

double Utils::randomFloat()
{
    return (rand() / (RAND_MAX + 1.0));
}

double Utils::randomInRange(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


double Utils::randomClamped()
{
    return (Utils::randomFloat() - Utils::randomFloat());
}
