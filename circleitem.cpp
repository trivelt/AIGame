#include "circleitem.h"
#include <QDebug>

CircleItem::CircleItem(double x, double y, double radius) :
    xVal(x),
    yVal(y),
    radiusVal(radius)
{
    ellipse = new QGraphicsEllipseItem(0, 0, radius*2, radius*2);
    setPos(x, y);
}

CircleItem::~CircleItem()
{

}

double CircleItem::radius() const
{
    return radiusVal;
}

double CircleItem::x()
{
    return xVal;
}

double CircleItem::y()
{
    return yVal;
}

void CircleItem::setPos(double x, double y)
{
    xVal = x;
    yVal = y;
    ellipse->setPos(x-radiusVal, y-radiusVal);
}

QPointF CircleItem::pos()
{
    return QPointF(xVal, yVal);
}

QGraphicsEllipseItem* CircleItem::getGraphicsItem()
{
    return ellipse;
}
