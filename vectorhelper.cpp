#include "vectorhelper.h"
#include <QMatrix>
#include <cmath>

void VectorHelper::truncateVector(QVector2D &vector, double max)
{
    if(vector.length() > max)
    {
        vector.normalize();
        vector *= max;
    }
}

QVector2D VectorHelper::normalize(const QVector2D &other)
{
    QVector2D vector = other;
    double vectorLength = other.length();
    if(vector.length() > VectorHelper::epsilon)
    {
        vector /= vectorLength;
    }
    return vector;
}

QVector2D VectorHelper::perpendicular(const QVector2D &other)
{
    return QVector2D(-other.y(), other.x());
}

double VectorHelper::distanceSq(const QVector2D &first, const QVector2D &second)
{
    double xSeparation = second.x() - first.x();
    double ySeparation = second.y() - first.y();

    return ySeparation*ySeparation + xSeparation*xSeparation;
}

double VectorHelper::lengthSq(const QVector2D &vector)
{
    return (vector.x()*vector.x() + vector.y()*vector.y());
}

QVector2D VectorHelper::pointToLocalSpace(const QVector2D &point, QVector2D heading, QVector2D side, QVector2D pos)
{
    double relativeX = point.x() - pos.x();
    double relativeY = point.y() - pos.y();

    double angle = atan2(heading.y(), heading.x());
    double rotatedX = cos(-angle)*relativeX - sin(-angle)*relativeY;
    double rotatedY = cos(-angle)*relativeY + sin(-angle)*relativeX;

    return QVector2D(rotatedX, rotatedY);

//    QVector2D transPoint = point;
//    QMatrix matTransform;

//    double t_x = -QVector2D::dotProduct(pos, heading);
//    double t_y = -QVector2D::dotProduct(pos, side);

//    matTransform.setMatrix(heading.x(), side.x(), heading.y(), side.y(), t_x, t_y);
//    return transformVector(transPoint, matTransform);
}

QVector2D VectorHelper::pointToWorldSpace(const QVector2D &point, QVector2D heading, QVector2D pos)
{
    double angle = atan2(heading.y(), heading.x());

    double rotatedX = point.x()*cos(angle) - point.y()*sin(angle) + pos.x();
    double rotatedY = point.x()*sin(angle) - point.y()*cos(angle) + pos.x();
//    double rotatedX = cos(-angle)*relativeX - sin(-angle)*relativeY;
//    double rotatedY = cos(-angle)*relativeY + sin(-angle)*relativeX;

    return QVector2D(rotatedX, rotatedY);
}
