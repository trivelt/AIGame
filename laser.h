#ifndef LASER_H
#define LASER_H
#include "pixmapitem.h"
#include <QMouseEvent>

class GraphicsScene;

class Laser
{
public:
    Laser(GraphicsScene* scene);
    void loadLaser();
    double getTimeForLoad();
    void shot(QMouseEvent* event);

private:
    void extendLineToTheBoundariesOfScene(QLineF& line);
    void cutLineIfCollidesWithObjects(QLineF& line);
    void detectCollisionsWithEnemies(QLineF& line);
    void drawLine(const QLineF& line);

    GraphicsScene* scene;
    double timeForLoad;
};

#endif // LASER_H
