#ifndef __GRAPHICSSCENE__H__
#define __GRAPHICSSCENE__H__

#include <QtWidgets/QGraphicsScene>
#include <QtCore/QSet>
#include <QtCore/QState>
#include <QAction>

#include "hero.h"
#include "enemy.h"
#include "laser.h"

class PixmapItem;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:

    GraphicsScene(int x, int y, int width, int height);
    ~GraphicsScene();
    void setupScene();
    void clearScene();
    void showEndScreen();

    QGraphicsTextItem* getTextView();
    Hero* getHero();
    QList<Enemy*> getEnemies();
    QList<QGraphicsItem *> getCollidingObjects();

    void addItem(QGraphicsItem *item);
    bool collideWithObjects(PixmapItem *item, QPointF translationVector, bool enemy=false);
    void processHeroMove(QKeyEvent* event);
    void processLaserShot(QMouseEvent* event);
    void killEnemy(Enemy* enemy);

    int getScreenWidth();
    int getScreenHeight();

public slots:
    void updateScene();

private:
    void createEnemies();
    void createCollidingObjects();
    bool collideWithBorders(QRectF rect);
    bool collideWithObjectsInScene(PixmapItem* item, QRectF rect, bool enemy=false);
    QRectF getRectAfterTranslation(PixmapItem *item, QPointF translationVector);

    Hero *hero;
    QList<Enemy*> enemies;
    QList<QGraphicsItem*> collidingObjects;
    Laser *laser;
    QGraphicsTextItem *textItem;
    QGraphicsTextItem *pointsFrame;
    QGraphicsTextItem* laserInfo;
    int screenWidth;
    int screenHeight;
    bool endOfGame;
    double score;
};

#endif //__GRAPHICSSCENE__H__

