#include "vectorhelper.h"

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
