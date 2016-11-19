#include "graphicsscene.h"
#include "pixmapitem.h"
#include "logger.h"

GraphicsScene::GraphicsScene(int x, int y, int width, int height)
    : QGraphicsScene(x , y, width, height)
{
    PixmapItem *kolko1 = new PixmapItem(QString("kolko1"));
    kolko1->setPos(0,0);
    addItem(kolko1);

//    PixmapItem *backgroundItem = new PixmapItem(QString("background"));
//    backgroundItem->setZValue(1);
//    backgroundItem->setPos(0,0);
//    addItem(backgroundItem);
}

void GraphicsScene::setupScene()
{
    Logger::log("Setupping graphics scene");
}

void GraphicsScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}

void GraphicsScene::clearScene()
{

}
