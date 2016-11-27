#ifndef LASER_H
#define LASER_H
#include "pixmapitem.h"
#include <QMouseEvent>

class GraphicsScene;

class Laser
{
public:
    Laser(GraphicsScene* scene);
    void shot(QMouseEvent* event);

private:
    GraphicsScene* scene;
};

#endif // LASER_H
