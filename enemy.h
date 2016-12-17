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
    void updateAI(double timeElapsed);

private:
    SteeringBehaviors* steering;
    QVector2D velocity;
    QVector2D position;
    QVector2D heading;
    QVector2D side;
    double maxForce;
    double maxSpeed;
    double mass;
    double maxTurnRate;

};

#endif // ENEMY_H
