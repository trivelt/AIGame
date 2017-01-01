#include "circleitem.h"

CircleItem::CircleItem(double x, double y, double radius) :
    QGraphicsEllipseItem(x, y, radius, radius),
    radius(radius)
{
}

double CircleItem::getRadius() const
{
    return radius;
}
