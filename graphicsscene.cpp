#include "graphicsscene.h"
#include "pixmapitem.h"

GraphicsScene::GraphicsScene(int x, int y, int width, int height)
    : QGraphicsScene(x , y, width, height)
{
    PixmapItem *backgroundItem = new PixmapItem(QString("background"));
    backgroundItem->setZValue(1);
    backgroundItem->setPos(0,0);
    addItem(backgroundItem);
}

void GraphicsScene::setupScene()
{

}

void GraphicsScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}

void GraphicsScene::clearScene()
{

}
