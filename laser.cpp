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
    int heroCenterX = hero->x() + hero->size().width()/2;
    int heroCenterY =hero->y() + hero->size().height()/2;

    QGraphicsLineItem* laserLine = new QGraphicsLineItem(heroCenterX, heroCenterY, event->x(), event->y());
    QPen pen;
    pen.setColor("#008000");
    pen.setWidth(2);
    laserLine->setPen(pen);
    scene->addItem(laserLine);
    Utils::sleep(50);
    scene->removeItem(laserLine);
}
