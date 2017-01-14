#include "vehicle.h"
#include "graphicsscene.h"
#include <QBrush>

Vehicle::Vehicle(double x, double y, double radius, GraphicsScene *scene) :
    CircleItem(x, y, radius)
{
    scene->addItem(this->getGraphicsItem());
    this->scene = scene;
    setColor(Qt::blue);
}

void Vehicle::setColor(Qt::GlobalColor color)
{
    QBrush brush(color);
    getGraphicsItem()->setBrush(brush);
}

void Vehicle::setColor(QString colorString)
{
    QColor color;
    color.setNamedColor(colorString);
    QBrush brush(color);
    getGraphicsItem()->setBrush(brush);
}

double Vehicle::getSpeed() const
{
    return velocity.length();
}
