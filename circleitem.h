#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QGraphicsEllipseItem>

class CircleItem : public QGraphicsEllipseItem
{
public:
    CircleItem(double x, double y, double radius);
    double getRadius() const;

private:
    double radius;
};

#endif // CIRCLEITEM_H
