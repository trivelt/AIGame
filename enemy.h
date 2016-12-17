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

    inline QVector2D getVelocity() const {return velocity;}
    inline QVector2D getPosition() const {return position;}
    inline QVector2D getHeading() const {return heading;}
    inline QVector2D getSide() const {return side;}
    inline double getMaxForce() const {return maxForce;}
    inline double getMaxSpeed() const {return maxSpeed;}
    inline double getMaxTurnRate() const {return maxTurnRate;}

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
