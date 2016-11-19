#include "graphicsscene.h"
#include "logger.h"

GraphicsScene::GraphicsScene(int x, int y, int width, int height)
    : QGraphicsScene(x , y, width, height)
{
    kolko1 = new PixmapItem(QString("kolko1"));
    kolko1->setPos(0,0);
    addItem(kolko1);

//    PixmapItem *backgroundItem = new PixmapItem(QString("background"));
//    backgroundItem->setZValue(1);
//    backgroundItem->setPos(0,0);
//    addItem(backgroundItem);
}

GraphicsScene::~GraphicsScene()
{
    delete kolko1;
    kolko1 = nullptr;
}

void GraphicsScene::setupScene()
{
    Logger::log("Setupping graphics scene");
}


void GraphicsScene::updateScene()
{
    Logger::log("Updating scene");
    QPointF posPoint = kolko1->pos();
    int xPos = posPoint.x();
    kolko1->setPos(xPos+10,posPoint.y());
}


void GraphicsScene::clearScene()
{

}


void GraphicsScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}
