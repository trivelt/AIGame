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

double VectorHelper::distance(const QVector2D &first, const QVector2D &second)
{
    return sqrt(distanceSq(first, second));
}

double VectorHelper::lengthSq(const QVector2D &vector)
{
    return (vector.x()*vector.x() + vector.y()*vector.y());
}

QVector2D VectorHelper::rotateVector(const QVector2D &center, double radians, QVector2D point)
{
    double s = sin(radians);
    double c = cos(radians);

    double pointX = point.x();
    double pointY = point.y();
    pointX -= center.x();
    pointY -= center.y();

    double xNew = pointX * c - pointY * s;
    double yNew = pointX * s + pointY * c;

    pointX = xNew + center.x();
    pointY = yNew + center.y();

    return QVector2D(pointX, pointY);


//    float s = sin(angle);
//     float c = cos(angle);

//     // translate point back to origin:
//     p.x -= cx;
//     p.y -= cy;

//     // rotate point
//     float xnew = p.x * c - p.y * s;
//     float ynew = p.x * s + p.y * c;

//     // translate point back:
//     p.x = xnew + cx;
//     p.y = ynew + cy;
//     return p;


//    double newX = vector.x() * cos(radians) - vector.y() * sin(radians);
//    double newY = vector.x() * sin(radians) + vector.y() * cos(radians);
//    return QVector2D(newX, newY);
}

QVector2D VectorHelper::pointToLocalSpace(const QVector2D &point, QVector2D heading, QVector2D pos)
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

double VectorHelper::vectorToAngleRad(QVector2D vector)
{
    return atan2(vector.y(), vector.x());
}

double VectorHelper::vectorToAngleDeg(QVector2D vector)
{
    double rad = vectorToAngleRad(vector);
    return radToDeg(rad);
}

double VectorHelper::radToDeg(double angle)
{
    return angle * 180 / 3.14159265;
}
