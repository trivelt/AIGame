#include "enemy.h"
#include "graphicsscene.h"
#include "steeringbehaviors.h"
#include "vectorhelper.h"
#include "logger.h"
#include "utils.h"
#include <QTimer>

Enemy::Enemy(GraphicsScene *scene) :
    Vehicle(0, 0, 15, scene),
    maxForce(10),
    maxSpeed(1),
    maxTurnRate(100),
    mass(1)
{
    steering = new SteeringBehaviors(this, scene);

    setColor(Qt::red);
    getGraphicsItem()->setZValue(1000);
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
    qDebug() << "\n============= updateEnemy() called ================";
    qDebug() << "Before calling updateAI, owner velocity=" << getVelocity() << " (" << velocity << ")";
    updateAI(timeElapsed);
    double xMove = heading.x() * getSpeed();
    double yMove = heading.y() * getSpeed();

    if(!scene->collideWithObjects(this, QPointF(xMove, yMove)))
    {
        setPos(pos().x() + xMove, pos().y() + yMove);
    }



//    double xMove = 0.2;
//    double yMove = 0.9;
//    QVector2D veloc(xMove, yMove);
//    veloc = VectorHelper::normalize(veloc);
//    double speed = 0.4;
//    xMove = veloc.x()*speed;
//    yMove = veloc.y()*speed;

//    if(!scene->collideWithObjects(this, QPointF(xMove, yMove)))
//    {
//        setPos(pos().x() + xMove, pos().y() + yMove);
//    }



//    updateAI(timeElapsed);


//    QPointF positionOfHero = scene->getHero()->pos();
//    double xPosHero = positionOfHero.x();
//    double yPosHero = positionOfHero.y();


//    QPointF posPoint = pos();
//    double xPos = posPoint.x();
//    double yPos = posPoint.y();
//    double xMove = 0;
//    double yMove = 0;
//    if(xPos > xPosHero)
//    {
//        xMove--;
//    }
//    else if(xPos < xPosHero)
//    {
//        xMove++;
//    }

//    if(yPos > yPosHero)
//    {
//        yMove--;
//    }
//    else if(yPos < yPosHero)
//    {
//        yMove++;
//    }

//    if(!scene->collideWithObjects(this, QPointF(xMove, yMove), true))
//    {
//        setPos(xPos+xMove, yPos+yMove);
//    }
//    else
//    {
//        int trials=5;
//        while(trials)
//        {
//            int randX = qrand() % 4;
//            int randY = qrand() % 4;
//            if(!scene->collideWithObjects(this, QPointF(randX, randY)))
//            {
//                setPos(xPos+randX, yPos+randY);
//                break;
//            }
//            trials--;
//        }
//    }
}

void Enemy::updateAI(double timeElapsed)
{
    QVector2D steeringForce = steering->calculate();
    qDebug() << "Calculated steering force=" << steeringForce;
    QVector2D acceleration = steeringForce / mass;
    qDebug() << "Calculated acceleration = " << acceleration;

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

