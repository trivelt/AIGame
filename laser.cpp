#include "laser.h"
#include "logger.h"
#include "utils.h"
#include "graphicsscene.h"
#include "hero.h"
#include <QGraphicsLineItem>

Laser::Laser(GraphicsScene *scene)
{
    this->scene = scene;
}


void Laser::shot(QMouseEvent *event)
{
    Hero* hero = scene->getHero();
    double heroCenterX = hero->x() + hero->size().width()/2;
    double heroCenterY =hero->y() + hero->size().height()/2;

    QLineF line(heroCenterX, heroCenterY, event->x(), event->y());
    extendLineToTheBoundariesOfScene(line);
    cutLineIfCollidesWithObjects(line);
    drawLine(line);
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
    foreach (QGraphicsItem* object, scene->getCollidingObjects()) {
        QRectF boundingRect = object->sceneBoundingRect();
        QLineF leftLine(boundingRect.bottomLeft(), boundingRect.topLeft());
        QLineF rightLine(boundingRect.bottomRight(), boundingRect.topRight());
        QLineF topLine(boundingRect.topLeft(), boundingRect.topRight());
        QLineF bottomLine(boundingRect.bottomLeft(), boundingRect.bottomRight());
        const int numberOfLines = 4;
        QLineF lines[numberOfLines] = {leftLine, rightLine, topLine, bottomLine};

        QPointF intersectionPoint;
        for(int i=0; i<numberOfLines; i++)
        {
            QLineF otherLine = lines[i];
            if(line.intersect(otherLine, &intersectionPoint) == QLineF::BoundedIntersection)
                line.setP2(QPointF(intersectionPoint.x(), intersectionPoint.y()));
        }
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
