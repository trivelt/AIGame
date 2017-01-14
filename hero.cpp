#include "hero.h"
#include "graphicsscene.h"
#include <QKeyEvent>

Hero::Hero(GraphicsScene* scene) : Vehicle(0, 0, 16, scene)
{
    setColor("#008000");
}

void Hero::processKeyEvent(QKeyEvent *event)
{
    int key = event->key();

    if(key == Qt::Key::Key_Right)
    {
        goRight();
    }
    else if(key == Qt::Key::Key_Left)
    {
        goLeft();
    }
    else if(key == Qt::Key::Key_Up)
    {
        goUp();
    }
    else if(key == Qt::Key::Key_Down)
    {
        goDown();
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
            scene->getTextView()->setHtml("x=" + QString::number(xPos+x) + ", y=" + QString::number(yPos+y));
        }
        else
        {
            break;
        }
    }

}
