#include "enemy.h"
#include "graphicsscene.h"
#include "logger.h"
#include <QTimer>

Enemy::Enemy(GraphicsScene *scene) : PixmapItem(QString("enemy"), scene)
{
}

void Enemy::updateEnemy()
{
    static bool yourTurn = false;
    yourTurn = !yourTurn;

    if(yourTurn)
    {
        QPointF positionOfHero = scene->getHero()->pos();
        int xPosHero = positionOfHero.x();
        int yPosHero = positionOfHero.y();


        QPointF posPoint = pos();
        int xPos = posPoint.x();
        int yPos = posPoint.y();
        int xMove = 0;
        int yMove = 0;
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

        if(!scene->collideWithObjects(this, QPoint(xMove, yMove)))
        {
            setPos(xPos+xMove, yPos+yMove);
        }
    }

    QTimer::singleShot(10, this, SLOT(updateEnemy()));

}
