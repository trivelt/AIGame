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
    static double lengthSq(const QVector2D& vector);
    static QVector2D pointToLocalSpace(const QVector2D &point, QVector2D heading, QVector2D side, QVector2D pos);
    static QVector2D pointToWorldSpace(const QVector2D& point, QVector2D heading, QVector2D pos);

    static constexpr double epsilon = 0.00000001;

};

#endif // VECTORHELPER_H
