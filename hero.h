#ifndef HERO_H
#define HERO_H
#include "pixmapitem.h"

class GraphicsScene;

class Hero : public PixmapItem
{
public:
    Hero(GraphicsScene* scene);
    void processKeyEvent(QKeyEvent* event);

private:
    void goUp();
    void goDown();
    void goRight();
    void goLeft();
    void go(int x, int y, int steps);
};

#endif // HERO_H
