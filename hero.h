#ifndef HERO_H
#define HERO_H
#include "vehicle.h"

class GraphicsScene;

class Hero : public Vehicle
{
public:
    Hero(GraphicsScene* scene);
    void processKeyEvent(QKeyEvent* event);
    void updateVelocity();

private:
    void goUp();
    void goDown();
    void goRight();
    void goLeft();
    void go(int x, int y, int steps);

    double timeFromLastKeyEvent;
};

#endif // HERO_H
