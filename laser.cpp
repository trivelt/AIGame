#include "laser.h"
#include "logger.h"
#include "utils.h"
#include "graphicsscene.h"
#include "hero.h"
#include <QGraphicsLineItem>
#include <cmath>

Laser::Laser(GraphicsScene *scene)
{
    this->scene = scene;
    loadingProgress = 100;
}

void Laser::loadLaser()
{
    loadingProgress += 0.1;
}

double Laser::getLoadingProgress()
{
    return loadingProgress;
}

void Laser::shot(QMouseEvent *event)
{
//    if(loadingProgress < 100)
//        return;

    Hero* hero = scene->getHero();
    double heroCenterX = hero->x();
    double heroCenterY = hero->y();

    QLineF line(heroCenterX, heroCenterY, event->x(), event->y());
    extendLineToTheBoundariesOfScene(line);
    cutLineIfCollidesWithObjects(line);
    detectCollisionsWithEnemies(line);
    drawLine(line);

    loadingProgress = 0;
}

void Laser::extendLineToTheBoundariesOfScene(QLineF &line)
{
    int screenWidth = scene->getScreenWidth();
    int screenHeight = scene->getScreenHeight();

    QPointF intersectionPoint;
    QLineF topBorder(QPointF(0,0), QPointF(screenWidth,0));
    if(line.intersect(topBorder, &intersectionPoint)
            && ((line.x2() > line.x1() && line.x2() < intersectionPoint.x())
                || (line.x2() < line.x1() && line.x2() > intersectionPoint.x())))
    {
        line.setP2(QPointF(intersectionPoint.x(), intersectionPoint.y()));
    }

    QLineF bottomBorder(QPointF(0,screenHeight), QPointF(screenWidth,screenHeight));
    if(line.intersect(bottomBorder, &intersectionPoint)
            && ((line.x2() > line.x1() && line.x2() < intersectionPoint.x())
                || (line.x2() < line.x1() && line.x2() > intersectionPoint.x())))
    {
        line.setP2(QPointF(intersectionPoint.x(), intersectionPoint.y()));
    }
}

void Laser::cutLineIfCollidesWithObjects(QLineF &line)
{
    bool withEnemies = false;
    foreach (CircleItem* object, scene->getCollidingObjects(withEnemies))
    {
        if(object == scene->getHero())
            continue;

        QPointF intersectionPoint;
        if(Utils::intersect(line, object, intersectionPoint))
        {
            line.setP2(intersectionPoint);
        }
    }
}

void Laser::detectCollisionsWithEnemies(QLineF &line)
{
    QList<Enemy*> enemiesToKill;

    foreach (Enemy* enemy, scene->getEnemies())
    {
        QPointF intersectionPoint;
        if(Utils::intersect(line, enemy, intersectionPoint))
        {
            enemiesToKill.append(enemy);
        }
    }


    foreach(Enemy* enemy, enemiesToKill)
    {
        scene->killEnemy(enemy);
    }
}

void Laser::drawLine(const QLineF &line)
{
    QGraphicsLineItem* laserLine = new QGraphicsLineItem(line);
    QPen pen;
    pen.setColor("#008000");
    pen.setWidth(2);
    laserLine->setPen(pen);
    scene->addItem(laserLine);
    Utils::sleep(50);
    scene->removeItem(laserLine);
}
