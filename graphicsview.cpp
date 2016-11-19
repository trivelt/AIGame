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
    Logger::log("keyPressEvent " + event->text());
    GraphicsScene* gScene = (GraphicsScene*)scene();
    int key = event->key();

    if(key == Qt::Key::Key_Right)
    {
        gScene->goRight();
    }
    else if(key == Qt::Key::Key_Left)
    {
        gScene->goLeft();
    }
    else if(key == Qt::Key::Key_Up)
    {
        gScene->goUp();
    }
    else if(key == Qt::Key::Key_Down)
    {
        gScene->goDown();
    }

}
