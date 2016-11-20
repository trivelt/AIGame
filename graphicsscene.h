#ifndef __GRAPHICSSCENE__H__
#define __GRAPHICSSCENE__H__

#include <QtWidgets/QGraphicsScene>
#include <QtCore/QSet>
#include <QtCore/QState>
#include <QAction>

#include "hero.h"
#include "enemy.h"

class PixmapItem;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:

    GraphicsScene(int x, int y, int width, int height);
    ~GraphicsScene();
    void setupScene();
    void clearScene();

    QGraphicsTextItem* getTextView();
    Hero* getHero();

    void addItem(QGraphicsItem *item);
    bool collideWithObjects(PixmapItem *item, QPoint translationVector);
    void processHeroMove(QKeyEvent* event);

private:
    bool collideWithBorders(QRect rect);
    bool collideWithObjectsInScene(PixmapItem* item, QRect rect);
    QRect getRectAfterTranslation(PixmapItem *item, QPoint translationVector);

    Hero *hero;
    Enemy *enemy1;
    QGraphicsTextItem *textItem;
};

#endif //__GRAPHICSSCENE__H__

