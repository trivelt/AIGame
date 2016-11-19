#ifndef __GRAPHICSSCENE__H__
#define __GRAPHICSSCENE__H__

#include <QtWidgets/QGraphicsScene>
#include <QtCore/QSet>
#include <QtCore/QState>
#include <QAction>

#include "pixmapitem.h"

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:

    GraphicsScene(int x, int y, int width, int height);
    ~GraphicsScene();
    void setupScene();
    void updateScene();
    void clearScene();

    void goUp();
    void goDown();
    void goLeft();
    void goRight();

public slots:
    void updateSc();

private:
    void addItem(QGraphicsItem *item);

    PixmapItem *kolko1;
    PixmapItem *enemy1;
    QGraphicsTextItem *textItem;

};

#endif //__GRAPHICSSCENE__H__

