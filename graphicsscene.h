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
    void clearScene();

    void goUp();
    void goDown();
    void goLeft();
    void goRight();

public slots:
    void updateScene();

private:
    void goHero(int x, int y, int steps);
    void addItem(QGraphicsItem *item);
    bool collideWithPoint(PixmapItem *item, QPoint translationVector);

    PixmapItem *kolko1;
    PixmapItem *enemy1;
    QGraphicsTextItem *textItem;
};

#endif //__GRAPHICSSCENE__H__

