#ifndef STEERINGBEHAVIORS_H
#define STEERINGBEHAVIORS_H

#include <QObject>
#include <QVector2D>

class Enemy;

class SteeringBehaviors : public QObject
{
    Q_OBJECT
public:
    explicit SteeringBehaviors(QObject *parent = 0);

    QVector2D calculate();
    QVector2D forwardComponent();
    QVector2D sideComponent();

    void setPath();
    void setTarget(QVector2D target);
    void setTargetAgent(Enemy* agent);

    void seekOn();
    void fleeOn();
    void arriveOn();

    void seekOff();
    void fleeOff();
    void arriveOff();

signals:

public slots:

private:
    QVector2D seek(QVector2D&);
    QVector2D flee(QVector2D&);
    QVector2D arrive(QVector2D&);
};

#endif // STEERINGBEHAVIORS_H
