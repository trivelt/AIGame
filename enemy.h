#ifndef ENEMY_H
#define ENEMY_H
#include "pixmapitem.h"
#include <QVector2D>

class SteeringBehaviors;
class GraphicsScene;

class Enemy : public PixmapItem
{
Q_OBJECT

public:
    Enemy(GraphicsScene* scene);
    void removeFromScene();
    void updateEnemy(double timeElapsed);

private:
    SteeringBehaviors* steering;
    QVector2D velocity;
    QVector2D heading;
    double maxForce;
    double maxSpeed;
    double mass;

};

#endif // ENEMY_H
