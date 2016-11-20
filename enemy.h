#ifndef ENEMY_H
#define ENEMY_H
#include "pixmapitem.h"

class GraphicsScene;

class Enemy : public PixmapItem
{
Q_OBJECT

public:
    Enemy(GraphicsScene* scene);

public slots:
    void updateEnemy();

};

#endif // ENEMY_H
