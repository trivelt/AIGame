#include "steeringbehaviors.h"
#include "enemy.h"
#include "vectorhelper.h"
#include "utils.h"
#include "graphicsscene.h"
#include <algorithm>
#include <QDebug>
#include <limits>
#include <cmath>

SteeringBehaviors::SteeringBehaviors(Enemy *owner, GraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    owner(owner),
    wanderRadius(5),
    wanderJitter(50),
    wanderDistance(20),
    attackMode(false)
{
    hero = scene->getHero();
    wanderCounter = (int) Utils::randomInRange(-5000, 10000);

    double theta = Utils::randomFloat() * 2*3.14159265359;
    qDebug() << "Theta=" << theta;
    wanderTarget = QVector2D(wanderRadius * cos(theta),
                                wanderRadius * sin(theta));
    qDebug() << "Init wanderTarget=" << wanderTarget;
}

QVector2D SteeringBehaviors::calculate()
{
    QVector2D steeringForce;
    steeringForce += wallAvoidance();
    steeringForce += obstacleAvoidance() * 100;
    if(owner->isSelectedToDebugInfo())
    {
        scene->getDebugFrame()->setDebugText("obst.Avod. frc=" + QString::number(steeringForce.x(), 'f', 2) + ", " + QString::number(steeringForce.y(), 'f', 2));
    }

    steeringForce += wander();
//    if(ownerInGroup())
//    {
//        attackMode = true;
//    }

//    if(attackMode)
//    {
//        steeringForce += cohesion();
//        steeringForce += pursuit(hero)*10;
//    }
//    else
//    {
//        wanderCounter++;
//        if(wanderCounter >= 25000 && wanderCounter<40000)
//        {
//            steeringForce += wander()*10;
//            steeringForce += hide(hero)*3;
//            steeringForce += cohesion()*8;
//        }
//        else
//        {
//            steeringForce += hide(hero)*3;
//            steeringForce += evade(hero)*4;
//            steeringForce += cohesion();

//            if(wanderCounter>=40000)
//            {
//                wanderCounter = 0;
//            }
//        }

//    }

    VectorHelper::truncateVector(steeringForce, owner->getMaxForce());
    return steeringForce;
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

void SteeringBehaviors::setTargetAgent(Vehicle* agent)
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

bool SteeringBehaviors::ownerInGroup()
{
    double range = owner->radius()*2 + 200;

    int neighborCount = 0;
    foreach (Vehicle* neighbor, scene->getEnemies())
    {
        if(owner == neighbor)
            continue;

        QVector2D distTo = neighbor->getPosition() - owner->getPosition();
        if(VectorHelper::lengthSq(distTo) < range*range)
        {
            neighborCount++;
        }
    }
    qDebug() << "neighborCount=" << neighborCount;
    return (neighborCount >= 6);
}

QVector2D SteeringBehaviors::seek(QVector2D targetPosition)
{
    QVector2D desiredVelocity = VectorHelper::normalize(targetPosition - owner->getPosition()) * owner->getMaxSpeed();
    return (desiredVelocity - owner->getVelocity());
}

QVector2D SteeringBehaviors::flee(QVector2D targetPosition)
{
    qDebug() << "Owner position=" << owner->getPosition() << ", targetPosition=" << targetPosition;
    const double panicDistanceSq = 200.0 * 200.0;
    if (VectorHelper::distanceSq(owner->getPosition(), targetPosition) > panicDistanceSq)
    {
        return QVector2D(0.0, 0.0);
    }

    QVector2D desiredVelocity = VectorHelper::normalize(owner->getPosition() - targetPosition) * owner->getMaxSpeed();
    qDebug() << "Flee is returning here: desiredVelocity=" << desiredVelocity << ", ownerVelcity=" << owner->getVelocity();
    return (desiredVelocity - owner->getVelocity());
}

QVector2D SteeringBehaviors::arrive(QVector2D targetPosition, Deceleration deceleration)
{
    QVector2D toTarget = targetPosition - owner->getPosition();
    double distance = toTarget.length();

    if (distance > 0)
    {
        const double decelerationTweaker = 0.3;
        double speed = distance / ((double)deceleration * decelerationTweaker);
        speed = std::min(speed, owner->getMaxSpeed());

        QVector2D desiredVelocity = toTarget * speed / distance;
        return (desiredVelocity - owner->getVelocity());
    }

    return QVector2D(0,0);
}

QVector2D SteeringBehaviors::pursuit(const Vehicle *evader)
{
    QVector2D toEvader = evader->getPosition() - owner->getPosition();
    double relativeHeading = QVector2D::dotProduct(owner->getHeading(), evader->getHeading());

    if ((QVector2D::dotProduct(toEvader, owner->getHeading()) > 0) && (relativeHeading < -0.95)) // 18 deg
    {
        return seek(evader->getPosition());
    }

    double lookAheadTime = toEvader.length() / (owner->getMaxSpeed() + evader->getSpeed());
    return seek(evader->getPosition() + evader->getVelocity() * lookAheadTime);
}

QVector2D SteeringBehaviors::evade(const Vehicle *pursuer)
{
    QVector2D toPursuer = pursuer->getPosition() - owner->getPosition();
    double lookAheadTime = toPursuer.length() / (owner->getMaxSpeed() + pursuer->getSpeed());
    qDebug() << "Pursuer speed=" << pursuer->getSpeed();
    return flee(pursuer->getPosition() + pursuer->getVelocity() * lookAheadTime);
}

QVector2D SteeringBehaviors::hide(Vehicle *target)
{
    double distToClosest = std::numeric_limits<double>::max();
    QVector2D bestHidingSpot;

    foreach (CircleItem* curOb, scene->getObstacles())
    {
        QVector2D hidingSpot = getHidingPosition(QVector2D(curOb->pos()), curOb->radius(), QVector2D(target->pos()));
        double dist = VectorHelper::distanceSq(hidingSpot, QVector2D(owner->pos()));

        if(dist < distToClosest)
        {
            distToClosest = dist;
            bestHidingSpot = hidingSpot;
        }
    }

    if(distToClosest == std::numeric_limits<double>::max())
    {
        return evade(target);
    }

    return arrive(bestHidingSpot, FAST);
}

QVector2D SteeringBehaviors::getHidingPosition(const QVector2D &posOb, const double radiusOb, const QVector2D &posTarget)
{
    const double distanceFromBoundary = 30.0;
    double distAway = radiusOb + distanceFromBoundary;
    QVector2D toOb = VectorHelper::normalize(posOb - posTarget);
    return (toOb * distAway) + posOb;
}

QVector2D SteeringBehaviors::wander()
{
    return QVector2D(1,0);
    QVector2D vectorToAdd= QVector2D(Utils::randomClamped() * wanderJitter,
                              Utils::randomClamped() * wanderJitter);
    wanderTarget += vectorToAdd;
    wanderTarget = VectorHelper::normalize(wanderTarget);
    wanderTarget *= wanderRadius;

    QVector2D targetLocal = wanderTarget + QVector2D(wanderDistance, 0);
    QVector2D targetWorld = VectorHelper::pointToWorldSpace(targetLocal, owner->getHeading(), owner->getPosition());

    return (targetWorld - owner->getPosition());
}

QVector2D SteeringBehaviors::cohesion()
{
    QVector2D centerOfMass, steeringForce;
    int neighborCount = 0;

    foreach (Vehicle* neighbor, scene->getEnemies())
    {
        if(owner == neighbor)
            continue;

        // instead of tagging neighbors
        QVector2D distTo = neighbor->getPosition() - owner->getPosition();
        double range = owner->radius() + neighbor->radius();
        if(VectorHelper::lengthSq(distTo) < range*range)
        {
            centerOfMass += neighbor->getPosition();
            neighborCount++;
        }
    }

    if(neighborCount > 0)
    {
        centerOfMass /= (double) neighborCount;
        steeringForce = seek(centerOfMass);
    }
    return steeringForce;
}

QVector2D SteeringBehaviors::obstacleAvoidance()
{
    double minDetectionBoxLength = 40;
    double dBoxLength = minDetectionBoxLength + (owner->getSpeed()/owner->getMaxSpeed()) * minDetectionBoxLength;

    if(DebugFrame::debugMode())
    {
//        qDebug() << "Position=" << owner->getPosition() << ", pos=" << owner->pos();
        QGraphicsRectItem* rect = new QGraphicsRectItem(owner->pos().x(), owner->pos().y()-owner->radius(), dBoxLength, owner->radius()*2);
        rect->setTransformOriginPoint(owner->pos());
        rect->setRotation(VectorHelper::vectorToAngleDeg(owner->getHeading()));
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(1);
        rect->setPen(pen);
        rect->setOpacity(0.1);
        scene->addItem(rect);
    }
//    return QVector2D(0,0);

    CircleItem* closestIntersectingObstacle = NULL;
    double distToClosestIP = std::numeric_limits<double>::max();
    QVector2D localPosOfClosestObstacle;

    foreach (CircleItem* obstacle, scene->getObstacles())
    {
        // instead of tagging
        QVector2D distTo = QVector2D(obstacle->pos()) - QVector2D(owner->getPosition());
        qDebug() << "obstaclePos=" << obstacle->pos() << ", ownerPos=" << owner->pos() <<
                    ", ownerPosition=" << owner->getPosition() << ", distToWithPosition=" << distTo <<
                    ", distToUsingOwnerPos= " <<  QVector2D(obstacle->pos()) - QVector2D(owner->pos())  ;
        double range = obstacle->radius() + owner->radius();
        if(VectorHelper::lengthSq(distTo) < range*range)
        {
            qDebug() << "HEREobstacle";
//            return QVector2D(0,-1);

            QVector2D localPos = VectorHelper::pointToLocalSpace(QVector2D(obstacle->pos()), owner->getHeading(), QVector2D(owner->getPosition()));
            if(localPos.x() >= 0)
            {
                QBrush br(Qt::red);
                obstacle->getGraphicsItem()->setBrush(br);
                double expandedRadius = obstacle->radius() + owner->radius();
                if(fabs(localPos.y()) < expandedRadius)
                {
                    double cX = localPos.x();
                    double cY = localPos.y();

                    double sqrtPart = sqrt(expandedRadius*expandedRadius - cY*cY);
                    double ip = cX - sqrtPart;

                    if(ip <= 0.0)
                    {
                        ip = cX + sqrtPart;
                    }

                    if(ip < distToClosestIP)
                    {
                        distToClosestIP = ip;
                        closestIntersectingObstacle = obstacle;
                        localPosOfClosestObstacle = localPos;
                    }
                }
            }
        }
    }


    QVector2D steeringForce;
    if(closestIntersectingObstacle)
    {
        double multiplier = 1.0 + (dBoxLength - localPosOfClosestObstacle.x()) / dBoxLength;
        steeringForce.setY( ((closestIntersectingObstacle->radius()) - localPosOfClosestObstacle.y()) * multiplier); // boundRadius?

        const double breakingWeight = 0.2;
        steeringForce.setX( ((closestIntersectingObstacle->radius()) - localPosOfClosestObstacle.x()) * breakingWeight); // boundingRadius
    }

    QVector2D localStartPoint(0,0);

    QVector2D worldStartPoint = VectorHelper::pointToWorldSpace(localStartPoint, owner->getHeading(), QVector2D(owner->getPosition()) );
    QVector2D worldEndPoint = VectorHelper::pointToWorldSpace(steeringForce, owner->getHeading(), QVector2D(owner->getPosition()) );

    return QVector2D(worldEndPoint-worldStartPoint);

}

QVector2D SteeringBehaviors::wallAvoidance()
{
    double wallDetectionFeelerLength = 100;

    QVector2D centerFeeler(owner->getPosition() + wallDetectionFeelerLength * owner->getHeading());
    QVector2D centerFeelerToRotations(owner->getPosition() + 80 * owner->getHeading());
    QVector2D leftFeeler(VectorHelper::rotateVector(owner->getPosition(), -0.785398, centerFeelerToRotations));
    QVector2D rightFeeler(VectorHelper::rotateVector(owner->getPosition(), 0.785398, centerFeelerToRotations));
//    QVector2D centerFeeler(owner->getPosition() + wallDetectionFeelerLength * owner->getHeading());
//    QVector2D leftFeeler = VectorHelper::rotateVector(centerFeeler, 0.785398);
//    QVector2D rightFeeler = VectorHelper::rotateVector(centerFeeler, -0.785398);
//    QVector2D leftFeeler, rightFeeler;
    QList<QVector2D> feelers;
    feelers.append(centerFeeler);
    feelers.append(leftFeeler);
    feelers.append(rightFeeler);


    if(DebugFrame::debugMode() && DebugFrame::feelerLines())
    {
        QGraphicsLineItem* lineLeft = new QGraphicsLineItem(QLineF(owner->getPosition().x(), owner->getPosition().y(), leftFeeler.x(), leftFeeler.y()));
        QGraphicsLineItem* lineRight = new QGraphicsLineItem(QLineF(owner->getPosition().x(), owner->getPosition().y(), rightFeeler.x(), rightFeeler.y()));
        QGraphicsLineItem* lineCenter = new QGraphicsLineItem(QLineF(owner->getPosition().x(), owner->getPosition().y(), centerFeeler.x(), centerFeeler.y()));
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(1);
        lineLeft->setPen(pen);
        lineLeft->setOpacity(0.6);
        scene->addItem(lineLeft);
        lineRight->setPen(pen);
        lineRight->setOpacity(0.6);
        scene->addItem(lineRight);
        lineCenter->setPen(pen);
        lineCenter->setOpacity(0.6);
        scene->addItem(lineCenter);
        Utils::sleep(15);
        scene->removeItem(lineLeft);
        scene->removeItem(lineRight);
        scene->removeItem(lineCenter);
    }


    double distToThisIP = 0.0;
    double distToClosestIP = std::numeric_limits<double>::max();
    QVector2D steeringForce, closestPoint;

    for(int i=0; i<feelers.size(); i++)
    {
        QVector2D feeler = feelers[i];
        QLineF feelerLine(owner->getPosition().x(), owner->getPosition().y(), feeler.x(), feeler.y());

        QLineF leftWall(0, 0, 0, scene->getScreenHeight());
        QLineF rightWall (scene->getScreenWidth(), 0, scene->getScreenWidth(), scene->getScreenHeight());
        QLineF topWall(0, 0, scene->getScreenWidth(), 0);
        QLineF bottomWall(0, scene->getScreenHeight(), scene->getScreenWidth(), scene->getScreenHeight());

        QPointF intersectionPoint;

        if(feelerLine.intersect(leftWall, &intersectionPoint) == QLineF::BoundedIntersection)
        {
            distToThisIP = VectorHelper::distance(QVector2D(intersectionPoint), owner->getPosition());
            if(distToThisIP < distToClosestIP)
            {
                distToClosestIP = distToThisIP;
                closestPoint = QVector2D(intersectionPoint);
//                qDebug() << "LEFT WALL, distToClosestIP=" << distToClosestIP << ", intersectionPoint=" << intersectionPoint;
            }
        }

        if(feelerLine.intersect(rightWall, &intersectionPoint) == QLineF::BoundedIntersection)
        {
            distToThisIP = VectorHelper::distance(QVector2D(intersectionPoint), owner->getPosition());
            if(distToThisIP < distToClosestIP)
            {
                distToClosestIP = distToThisIP;
                closestPoint = QVector2D(intersectionPoint);
//                qDebug() << "RIGHT WALL, distToClosestIP=" << distToClosestIP << ", intersectionPoint=" << intersectionPoint;

            }
        }

        if(feelerLine.intersect(topWall, &intersectionPoint) == QLineF::BoundedIntersection)
        {
            distToThisIP = VectorHelper::distance(QVector2D(intersectionPoint), owner->getPosition());
            if(distToThisIP < distToClosestIP)
            {
                distToClosestIP = distToThisIP;
                closestPoint = QVector2D(intersectionPoint);
//                qDebug() << "TOP WALL, distToClosestIP=" << distToClosestIP << ", intersectionPoint=" << intersectionPoint;

            }
        }

        if(feelerLine.intersect(bottomWall, &intersectionPoint) == QLineF::BoundedIntersection)
        {
            distToThisIP = VectorHelper::distance(QVector2D(intersectionPoint), owner->getPosition());
            if(distToThisIP < distToClosestIP)
            {
                distToClosestIP = distToThisIP;
                closestPoint = QVector2D(intersectionPoint);
//                qDebug() << "BOTTOM WALL, distToClosestIP=" << distToClosestIP << ", intersectionPoint=" << intersectionPoint;

            }
        }


        if(distToClosestIP < std::numeric_limits<double>::max())
        {
            QVector2D overShoot = feeler-QVector2D(closestPoint);
//            qDebug() << "overshoot length= " << overShoot.length();
//            qDebug() << "perpendicular to the closest=" << VectorHelper::perpendicular(closestPoint);
//            qDebug() << "Closest point=" << closestPoint;
            steeringForce = VectorHelper::perpendicular(closestPoint-owner->getPosition()) * overShoot.length();
        }
    }

    return steeringForce;
}
