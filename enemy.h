#ifndef ENEMY_H
#define ENEMY_H
#include "vehicle.h"
#include <QVector2D>

class SteeringBehaviors;
class GraphicsScene;

class Enemy : public Vehicle
{
public:
    Enemy(GraphicsScene* scene);
    static Enemy* createRandomEnemy(GraphicsScene* scene, double screenWidth, double screenHeight);
    void removeFromScene();
    void updateEnemy(double timeElapsed);
    void updateAI(double timeElapsed);

    inline double getMaxForce() const {return maxForce;}
    inline double getMaxSpeed() const {return maxSpeed;}
    inline double getMaxTurnRate() const {return maxTurnRate;}

    void selectToDebugInfo(bool select);
    bool isSelectedToDebugInfo();

private:
    SteeringBehaviors* steering;
    double maxForce;
    double maxSpeed;
    double mass;
    double maxTurnRate;

    bool selectedToDebugInfo;
    Qt::GlobalColor defaultColor;

};

#endif // ENEMY_H
