#include "enemy.h"
#include "graphicsscene.h"
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
        if(xPos > xPosHero)
        {
            xPos--;
        }
        else if(xPos < xPosHero)
        {
            xPos++;
        }

        if(yPos > yPosHero)
        {
            yPos--;
        }
        else if(yPos < yPosHero)
        {
            yPos++;
        }

        setPos(xPos, yPos);
    }

    QTimer::singleShot(10, this, SLOT(updateEnemy()));

}
