#include "enemy.h"
#include "graphicsscene.h"
#include "steeringbehaviors.h"
#include "vectorhelper.h"
#include "logger.h"
#include "utils.h"
#include <QTimer>

Enemy::Enemy(GraphicsScene *scene) :
    Vehicle(0, 0, 16, scene),
    maxForce(2),
    maxSpeed(3.7),
    maxTurnRate(100),
    mass(1)
{
    steering = new SteeringBehaviors(this, scene);
    selectedToDebugInfo = false;
    defaultColor = Qt::red;
    setColor(defaultColor);
}

Enemy *Enemy::createRandomEnemy(GraphicsScene *scene, double screenWidth, double screenHeight)
{
    Enemy* enemy = new Enemy(scene);

    double randX = Utils::randomInRange(0, screenWidth);
    double randY = Utils::randomInRange(0, screenHeight);
    enemy->setPos(randX, randY);

    while(scene->collideWithObjects(enemy, QPointF(0,0)))
    {
        randX = Utils::randomInRange(0, screenWidth);
        randY = Utils::randomInRange(0, screenHeight);
        enemy->setPos(randX, randY);
    }

    return enemy;
}

void Enemy::removeFromScene()
{
    scene->removeItem(getGraphicsItem());
}

void Enemy::updateEnemy(double timeElapsed)
{
//    qDebug() << "\n============= updateEnemy() called ================";
//    qDebug() << "Before calling updateAI, owner velocity=" << getVelocity() << " (" << velocity << ")";
    updateAI(timeElapsed);
    double xMove = heading.x() * getSpeed();
    double yMove = heading.y() * getSpeed();

    if(DebugFrame::debugMode() && selectedToDebugInfo)
    {
        scene->getDebugFrame()->setAgentTargetVector(heading);
    }

    if(!scene->collideWithObjects(this, QPointF(xMove, yMove), true))
    {
        setPos(pos().x() + xMove, pos().y() + yMove);
        position.setX(pos().x()+xMove);
        position.setY(pos().y()+yMove);
    }
}

void Enemy::updateAI(double timeElapsed)
{
    QVector2D steeringForce = steering->calculate();
//    qDebug() << "Calculated steering force=" << steeringForce;
    QVector2D acceleration = steeringForce / mass;
//    qDebug() << "Calculated acceleration = " << acceleration;

    // update velocity
    velocity += acceleration*timeElapsed;
    VectorHelper::truncateVector(velocity, maxSpeed);

//     update position
//    position += velocity*timeElapsed;

    if (velocity.lengthSquared() > VectorHelper::epsilon)
    {
        heading = VectorHelper::normalize(velocity);
        side = VectorHelper::perpendicular(heading);
    }
}

void Enemy::selectToDebugInfo(bool select)
{
    selectedToDebugInfo = select;
    if(selectedToDebugInfo)
    {
        setColor(Qt::black);
    }
    else
    {
        setColor(defaultColor);
    }
}

bool Enemy::isSelectedToDebugInfo()
{
    return selectedToDebugInfo;
}
