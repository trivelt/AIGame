#include "steeringbehaviors.h"
#include "enemy.h"
#include "vectorhelper.h"
#include <algorithm>

SteeringBehaviors::SteeringBehaviors(Enemy *owner, QObject *parent) : QObject(parent)
{
    this->owner = owner;
}

QVector2D SteeringBehaviors::calculate()
{

}

QVector2D SteeringBehaviors::forwardComponent()
{

}

QVector2D SteeringBehaviors::sideComponent()
{

}

void SteeringBehaviors::setPath()
{

}

void SteeringBehaviors::setTarget(QVector2D target)
{

}

void SteeringBehaviors::setTargetAgent(Enemy* agent)
{

}

void SteeringBehaviors::seekOn()
{

}

void SteeringBehaviors::fleeOn()
{

}

void SteeringBehaviors::arriveOn()
{

}

void SteeringBehaviors::seekOff()
{

}

void SteeringBehaviors::fleeOff()
{

}

void SteeringBehaviors::arriveOff()
{

}

QVector2D SteeringBehaviors::seek(QVector2D targetPosition)
{
    QVector2D desiredVelocity = VectorHelper::normalize(targetPosition - owner->getPosition()) * owner->getMaxSpeed();
    return (desiredVelocity - owner->getVelocity());
}

QVector2D SteeringBehaviors::flee(QVector2D targetPosition)
{
    const double panicDistanceSq = 100.0 * 100.0;
    if(VectorHelper::distanceSq(owner->getPosition(), targetPosition) > panicDistanceSq)
        return QVector2D(0.0, 0.0);

    QVector2D desiredVelocity = VectorHelper::normalize(owner->getPosition() - targetPosition) * owner->getMaxSpeed();
    return (desiredVelocity - owner->getVelocity());
}

QVector2D SteeringBehaviors::arrive(QVector2D targetPosition, Deceleration deceleration)
{
    QVector2D toTarget = targetPosition - owner->getPosition();
    double distance = toTarget.length();

    if(distance > 0)
    {
        const double decelerationTweaker = 0.3;
        double speed = distance / ((double)deceleration * decelerationTweaker);
        speed = std::min(speed, owner->getMaxSpeed());

        QVector2D desiredVelocity = toTarget * speed / distance;
        return (desiredVelocity - owner->getVelocity());
    }

    return QVector2D(0,0);
}
