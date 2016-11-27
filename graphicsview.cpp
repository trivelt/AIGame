#include "graphicsview.h"
#include "graphicsscene.h"
#include "logger.h"
#include <QKeyEvent>

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{

}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
//    Logger::log("keyPressEvent " + event->text());
    GraphicsScene* gScene = (GraphicsScene*)scene();
    gScene->processHeroMove(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    GraphicsScene* gScene = (GraphicsScene*)scene();
    gScene->processLaserShot(event);
}
