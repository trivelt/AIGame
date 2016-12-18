#ifndef STEERINGBEHAVIORS_H
#define STEERINGBEHAVIORS_H

#include <QObject>
#include <QVector2D>

class Enemy;

enum Deceleration
{
    SLOW = 3,
    NORMAL = 2,
    FAST = 1
};

class SteeringBehaviors : public QObject
{
    Q_OBJECT
public:
    explicit SteeringBehaviors(Enemy* owner, QObject *parent = 0);

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
    QVector2D seek(QVector2D targetPosition);
    QVector2D flee(QVector2D targetPosition);
    QVector2D arrive(QVector2D targetPosition, Deceleration deceleration);
    QVector2D pursuit(const Enemy* evader);
    QVector2D evade(const Enemy* pursuer);
    QVector2D wander();

    Enemy* owner;

    double wanderRadius;
    double wanderDistance;
    double wanderJitter;
    QVector2D wanderTarget;

};

#endif // STEERINGBEHAVIORS_H
