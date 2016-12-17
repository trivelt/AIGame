#include "enemy.h"
#include "graphicsscene.h"
#include "steeringbehaviors.h"
#include "vectorhelper.h"
#include "logger.h"
#include <QTimer>

Enemy::Enemy(GraphicsScene *scene) :
    PixmapItem(QString("enemy"), scene),
    maxForce(10),
    maxSpeed(50),
    maxTurnRate(100)
{
    steering = new SteeringBehaviors();
}

void Enemy::removeFromScene()
{
    scene->removeItem(this);
}

void Enemy::updateEnemy(double timeElapsed)
{

    QPointF positionOfHero = scene->getHero()->pos();
    double xPosHero = positionOfHero.x();
    double yPosHero = positionOfHero.y();


    QPointF posPoint = pos();
    double xPos = posPoint.x();
    double yPos = posPoint.y();
    double xMove = 0;
    double yMove = 0;
    if(xPos > xPosHero)
    {
        xMove--;
    }
    else if(xPos < xPosHero)
    {
        xMove++;
    }

    if(yPos > yPosHero)
    {
        yMove--;
    }
    else if(yPos < yPosHero)
    {
        yMove++;
    }

    if(!scene->collideWithObjects(this, QPointF(xMove, yMove), true))
    {
        setPos(xPos+xMove, yPos+yMove);
    }
    else
    {
        int trials=5;
        while(trials)
        {
            int randX = qrand() % 4;
            int randY = qrand() % 4;
            if(!scene->collideWithObjects(this, QPointF(randX, randY)))
            {
                setPos(xPos+randX, yPos+randY);
                break;
            }
            trials--;
        }
    }
}

void Enemy::updateAI(double timeElapsed)
{
    QVector2D steeringForce = steering->calculate();
    QVector2D acceleration = steeringForce / mass;

    // update velocity
    velocity += acceleration*timeElapsed;
    VectorHelper::truncateVector(velocity, maxSpeed);

    // update position
    position += velocity*timeElapsed;

    if (velocity.lengthSquared() > VectorHelper::epsilon)
    {
        heading = VectorHelper::normalize(velocity);
        side = VectorHelper::perpendicular(heading);
    }
}
