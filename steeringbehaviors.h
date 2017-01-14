#ifndef STEERINGBEHAVIORS_H
#define STEERINGBEHAVIORS_H

#include <QObject>
#include <QVector2D>
#include "vehicle.h"

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
    explicit SteeringBehaviors(Enemy* owner, GraphicsScene* scene, QObject *parent = 0);

    QVector2D calculate();
    QVector2D forwardComponent();
    QVector2D sideComponent();

    void setPath();
    void setTarget(QVector2D target);
    void setTargetAgent(Vehicle *agent);

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
    QVector2D pursuit(const Vehicle *evader);
    QVector2D evade(const Vehicle* pursuer);
    QVector2D wander();

    Enemy* owner;
    Vehicle* hero;

    double wanderRadius;
    double wanderDistance;
    double wanderJitter;
    QVector2D wanderTarget;

    GraphicsScene* scene;
};

#endif // STEERINGBEHAVIORS_H
