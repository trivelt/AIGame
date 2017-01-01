#include "vehicle.h"
#include "graphicsscene.h"
#include <QBrush>

Vehicle::Vehicle(double x, double y, double radius, GraphicsScene *scene) :
    CircleItem(x, y, radius)
{
    scene->addItem(this);
    this->scene = scene;
    setColor(Qt::blue);
}

void Vehicle::setColor(Qt::GlobalColor color)
{
    QBrush brush(color);
    setBrush(brush);
}

double Vehicle::getSpeed() const
{
    return velocity.length();
}
