#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QGraphicsEllipseItem>

class CircleItem
{

public:
    CircleItem(double x, double y, double radiusVal);
    virtual ~CircleItem();
    double radius() const;
    double boundingRadius() const;
    double x();
    double y();
    void setPos(double x, double y);
    QPointF pos();
    QGraphicsEllipseItem* getGraphicsItem();

private:
    double xVal;
    double yVal;
    double radiusVal;

    QGraphicsEllipseItem* ellipse;
};

#endif // CIRCLEITEM_H
