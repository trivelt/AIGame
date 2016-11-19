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
    if(event->key() == Qt::Key::Key_Right) {
        Logger::log("Key Right Arrow");
        GraphicsScene* gScene = (GraphicsScene*)scene();
        gScene->updateScene();
    }
}
