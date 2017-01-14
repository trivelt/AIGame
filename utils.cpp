#include "utils.h"
#include <QTimer>
#include <QEventLoop>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <QDebug>

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

bool Utils::intersect(QLineF& line, CircleItem* circle, QPointF& intersectionPoint)
{
    // http://stackoverflow.com/a/1088058/3424163
    double LAB = sqrt(  pow(line.x2()-line.x1(), 2) + pow(line.y2()-line.y1(), 2) );
    double Dx = (line.x2()-line.x1()) / LAB;
    double Dy = (line.y2()-line.y1()) / LAB;
    double t = Dx*(circle->x()-line.x1()) + Dy*(circle->y()-line.y1());
    double Ex = t*Dx+line.x1();
    double Ey = t*Dy+line.y1();
    double LEC = sqrt( pow(Ex-circle->x(), 2) + pow(Ey-circle->y(), 2)  );

    if( LEC < circle->radius() )
    {
        double dt = sqrt( pow(circle->radius(), 2) - pow(LEC, 2)  );

        double Fx = (t-dt)*Dx + line.x1();
        double Fy = (t-dt)*Dy + line.y1();

//        double Gx = (t+dt)*Dx + line.x1();
//        double Gy = (t+dt)*Dy + line.y1();

        if(! ((line.x2() < line.x1() && ( Fx > line.x1() || Fx < line.x2()) )
              || (line.x2() > line.x1() && ( Fx < line.x1() || Fx > line.x2()) )
            ))
        {
            intersectionPoint.setX(Fx);
            intersectionPoint.setY(Fy);
            return true;
        }
    }
    else if( LEC ==  circle->radius())
    {
        intersectionPoint.setX(Ex);
        intersectionPoint.setY(Ey);
        return true;
    }

    return false;
}
