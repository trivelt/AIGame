#include "graphicsview.h"
#include "graphicsscene.h"
#include "logger.h"
#include <QKeyEvent>

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
//    Logger::log("keyPressEvent " + event->text());
    GraphicsScene* gScene = (GraphicsScene*)scene();

    int key = event->key();
    if(key == Qt::Key_D)
    {
        DebugFrame::turnDebugMode();
        gScene->showDebugFrame();
    }
    else if(key == Qt::Key_L)
    {
        DebugFrame::showFeelerLines();
    }
    else if(key == Qt::Key_N && DebugFrame::debugMode())
    {
        gScene->debugNextEnemy();
    }
    else
    {
        gScene->processHeroMove(event);
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    GraphicsScene* gScene = (GraphicsScene*)scene();
    gScene->processLaserShot(event);
}

