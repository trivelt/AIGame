#include "hero.h"
#include "utils.h"
#include "graphicsscene.h"
#include "vectorhelper.h"
#include <QKeyEvent>
#include <QDebug>

Hero::Hero(GraphicsScene* scene) : Vehicle(0, 0, 16, scene)
{
    timeFromLastKeyEvent = 100;
    setColor("#008000");
}

void Hero::processKeyEvent(QKeyEvent *event)
{
    int key = event->key();

    if(key == Qt::Key_Right)
    {
        velocity.setX(10);
        velocity.setY(0);
        goRight();
    }
    else if(key == Qt::Key_Left)
    {
        velocity.setX(-10);
        velocity.setY(0);
        goLeft();
    }
    else if(key == Qt::Key_Up)
    {
        velocity.setX(0);
        velocity.setY(-10);
        goUp();
    }
    else if(key == Qt::Key_Down)
    {
        velocity.setX(0);
        velocity.setY(10);
        goDown();
    }
    heading = VectorHelper::normalize(velocity);
    side = VectorHelper::perpendicular(heading);
    timeFromLastKeyEvent = 0;

//    QGraphicsRectItem* rect = new QGraphicsRectItem(pos().x(), pos().y()-radius(), 100, radius()*2);
//    rect->setTransformOriginPoint(pos());
//    qDebug() << "Vector to angle=" << VectorHelper::vectorToAngleDeg(QVector2D(0,1));
//    rect->setRotation(VectorHelper::vectorToAngleDeg(heading));
//    QPen pen;
//    pen.setColor(Qt::green);
//    pen.setWidth(1);
//    rect->setPen(pen);
//    scene->addItem(rect);
//    Utils::sleep(500);
//    scene->removeItem(rect);


    double wallDetectionFeelerLength = 60;
    QVector2D centerFeeler(getPosition() + wallDetectionFeelerLength * getHeading());
    QVector2D centerFeelerToRotations(getPosition() + 40 * getHeading());
    QVector2D leftFeeler(VectorHelper::rotateVector(getPosition(), -0.785398, centerFeelerToRotations));
    QVector2D rightFeeler(VectorHelper::rotateVector(getPosition(), 0.785398, centerFeelerToRotations));

//    scene->getDebugFrame()->setDebugText("Center feeler=" + QString::number(centerFeeler.x(), 'f', 2) + ", " + QString::number(centerFeeler.y(), 'f', 2));
//    qDebug() << "Center feeler=" << centerFeeler;


//    QVector2D rotatedCenterToLeft = VectorHelper::rotateVector(getPosition(), -0.785398, centerFeeler);
//    qDebug() << "rotatedCenterToLeft=" << rotatedCenterToLeft << ", angle 0.785398 in deg=" << VectorHelper::radToDeg(0.785398);
//    QVector2D leftFeeler = rotatedCenterToLeft;
//    leftFeeler.normalize();

//    QVector2D rightFeeler = VectorHelper::rotateVector(centerFeeler, -0.785398);
//    QVector2D rightFeeler;

    if(DebugFrame::debugMode() && DebugFrame::feelerLines())
    {
        QLineF centerLineOb(getPosition().x(), getPosition().y(), centerFeeler.x(), centerFeeler.y());
        QGraphicsLineItem* lineLeft = new QGraphicsLineItem(QLineF(getPosition().x(), getPosition().y(), leftFeeler.x(), leftFeeler.y()));
        QGraphicsLineItem* lineRight = new QGraphicsLineItem(QLineF(getPosition().x(), getPosition().y(), rightFeeler.x(), rightFeeler.y()));
        QGraphicsLineItem* lineCenter = new QGraphicsLineItem(centerLineOb);
        qDebug() << "LineCenter=" << centerLineOb;
        QPen pen;
        pen.setColor(Qt::green);
        pen.setWidth(5);
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

}

void Hero::updateVelocity()
{
    timeFromLastKeyEvent++;
    if(timeFromLastKeyEvent > 50)
    {
        velocity.setX(0);
        velocity.setY(0);
    }
}

void Hero::goDown()
{
    go(0, 1, 10);
}

void Hero::goUp()
{
    go(0, -1, 10);
}

void Hero::goRight()
{
    go(1, 0, 10);
}

void Hero::goLeft()
{
    go(-1, 0, 10);
}

void Hero::go(int x, int y, int steps)
{

//    QPointF posPoint = pos();
//    int xPos = posPoint.x();
//    int yPos = posPoint.y();
//    setPos(xPos+x, yPos+y);
    for(int i=0;i <steps; i++)
    {
        if(!scene->collideWithObjects(this, QPoint(x, y)))
        {
            QPointF posPoint = pos();
            int xPos = posPoint.x();
            int yPos = posPoint.y();
            setPos(xPos+x, yPos+y);
            position = QVector2D(pos()); //TODO: to improve

            if(DebugFrame::debugMode())
            {
                scene->getDebugFrame()->setHeroPosition(xPos+x, yPos+y);
            }
        }
        else
        {
            break;
        }
    }

}
