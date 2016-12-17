#ifndef VECTORHELPER_H
#define VECTORHELPER_H

#include <QVector2D>

class VectorHelper
{
public:
    static void truncateVector(QVector2D& vector, double max);
    static QVector2D normalize(const QVector2D& other);
    static QVector2D perpendicular(const QVector2D& other);
    static double distanceSq(const QVector2D& first, const QVector2D& second);

    static const double epsilon = 0.00000001;

};

#endif // VECTORHELPER_H
