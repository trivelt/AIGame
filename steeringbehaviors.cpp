#include "steeringbehaviors.h"

SteeringBehaviors::SteeringBehaviors(QObject *parent) : QObject(parent)
{

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

QVector2D SteeringBehaviors::seek(QVector2D&)
{

}

QVector2D SteeringBehaviors::flee(QVector2D&)
{

}

QVector2D SteeringBehaviors::arrive(QVector2D&)
{

}
