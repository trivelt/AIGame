#ifndef UTILS_H
#define UTILS_H

#include "circleitem.h"

class Utils
{
public:
    static void sleep(int msec);
    static void initRandoms();
    static double randomFloat();
    static double randomInRange(double fMin, double fMax);
    static double randomClamped();
    static bool intersect(QLineF &line, CircleItem *circle, QPointF&);

};

#endif // UTILS_H
