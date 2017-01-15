#include "hero.h"
#include "graphicsscene.h"
#include "vectorhelper.h"
#include <QKeyEvent>

Hero::Hero(GraphicsScene* scene) : Vehicle(0, 0, 16, scene)
{
    timeFromLastKeyEvent = 100;
    setColor("#008000");
}

void Hero::processKeyEvent(QKeyEvent *event)
{
    int key = event->key();

    if(key == Qt::Key::Key_Right)
    {
        velocity.setX(10);
        velocity.setY(0);
        goRight();
    }
    else if(key == Qt::Key::Key_Left)
    {
        velocity.setX(-10);
        velocity.setY(0);
        goLeft();
    }
    else if(key == Qt::Key::Key_Up)
    {
        velocity.setX(0);
        velocity.setY(10);
        goUp();
    }
    else if(key == Qt::Key::Key_Down)
    {
        velocity.setX(0);
        velocity.setY(-10);
        goDown();
    }
    heading = VectorHelper::normalize(velocity);
    side = VectorHelper::perpendicular(heading);
    timeFromLastKeyEvent = 0;
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

#ifdef DEBUG_GAME
            scene->getDebugFrame()->setHeroPosition(xPos+x, yPos+y);
#endif
//            scene->getTextView()->setHtml("x=" + QString::number(xPos+x) + ", y=" + QString::number(yPos+y));
        }
        else
        {
            break;
        }
    }

}
