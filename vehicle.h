#ifndef VEHICLE_H
#define VEHICLE_H
#include <QVector2D>
#include "circleitem.h"

class GraphicsScene;

class Vehicle : public CircleItem
{
public:
    Vehicle(double x, double y, double radius, GraphicsScene* scene);

    void setColor(Qt::GlobalColor color);
    void setColor(QString colorString);
    double getSpeed() const;
    inline QVector2D getVelocity() const {return velocity;}
    inline QVector2D getPosition() const {return position;}
    inline QVector2D getHeading() const {return heading;}
    inline QVector2D getSide() const {return side;}

protected:
    QVector2D velocity;
    QVector2D position;
    QVector2D heading;
    QVector2D side;

    GraphicsScene* scene;
};

#endif // VEHICLE_H
