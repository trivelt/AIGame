#include "vehicle.h"
#include "graphicsscene.h"
#include <QBrush>
#include <QDebug>

Vehicle::Vehicle(double x, double y, double radius, GraphicsScene *scene) :
    CircleItem(x, y, radius)
{
    scene->addItem(this->getGraphicsItem());
    this->scene = scene;
    setColor(Qt::blue);

    velocity.setX(0);
    velocity.setY(0);
    position.setX(x);
    position.setY(y);
    heading.setX(0);
    heading.setY(0);
    side.setX(0);
    side.setY(0);

    qDebug() << "Created vehicle and set velocity: " << velocity;
}

void Vehicle::setPos(double x, double y)
{
    CircleItem::setPos(x, y);
    position.setX(x);
    position.setY(y);
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
