#include "graphicsscene.h"
#include "logger.h"
#include "utils.h"
#include "vehicle.h"

#include <QTimer>
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QDebug>
#include <cmath>

GraphicsScene::GraphicsScene(int x, int y, int width, int height)
    : QGraphicsScene(x , y, width, height)
{    
    Utils::initRandoms();
    endOfGame = false;
    numberOfDebuggedEnemy = 0;
    score = 0;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    screenWidth = screenGeometry.width();
    screenHeight = screenGeometry.height();

    createTextItems();
    createObstacles();

    hero = new Hero(this);
    hero->setPos(hero->radius(), hero->radius());

    createEnemies(3);
    laser = new Laser(this);
}

GraphicsScene::~GraphicsScene()
{
    delete hero;
    hero = NULL;

    foreach (Enemy* enemy, enemies) {
        enemies.removeOne(enemy);
        delete enemy;
    }
    delete debugFrame;
}

void GraphicsScene::setupScene()
{
    updateScene();
}

void GraphicsScene::updateScene()
{
    if(endOfGame)
        return;

    hero->updateVelocity();
    foreach (Enemy* enemy, enemies) {
        enemy->updateEnemy(100);
    }

    updateTextItems();
    QTimer::singleShot(10, this, SLOT(updateScene()));
}

void GraphicsScene::updateTextItems()
{
    score += 0.01;
    QString scoreText = "Score: " + QString::number(score);
    pointsFrame->setPlainText(scoreText);

    if(laser->getLoadingProgress() < 100)
    {
        laser->loadLaser();
        double currentLoadingState = laser->getLoadingProgress();
        QString laserText = "Laser ready to shoot";

        if(currentLoadingState < 100)
            laserText = "Laser loading progress: " + QString::number((int)currentLoadingState) + "%";

        laserInfo->setPlainText(laserText);
    }
}

void GraphicsScene::clearScene()
{
}

void GraphicsScene::showEndScreen()
{
    removeItem(pointsFrame);

    QGraphicsRectItem* backgroundRect = new QGraphicsRectItem(screenWidth/10, screenHeight/10, screenWidth*0.8, screenHeight*0.8);
    backgroundRect->setBrush(Qt::gray);
    backgroundRect->setZValue(100);
    addItem(backgroundRect);

    QGraphicsTextItem* endText = new QGraphicsTextItem();
    endText->setPos(screenWidth*0.35, screenHeight*0.3);
    QFont font;
    font.setPointSize(20);
    endText->setFont(font);
    endText->setHtml("<h1>GAME OVER</h1><br /> <br />&nbsp;&nbsp;&nbsp;Your score: " + QString::number(score) + " points");
    endText->setZValue(150);
    addItem(endText);
}

void GraphicsScene::processHeroMove(QKeyEvent *event)
{
    if(!endOfGame)
        hero->processKeyEvent(event);
}

void GraphicsScene::processLaserShot(QMouseEvent *event)
{
    if(endOfGame)
        return;

    int numberOfEnemies = enemies.size();
    laser->shot(event);
    int killedEnemies = numberOfEnemies - enemies.size();
    score += 100*killedEnemies;

    if(enemies.size() == 0)
    {
        score += (0.9/score*500000);
        endOfGame = true;
        showEndScreen();
    }
}

void GraphicsScene::killEnemy(Enemy *enemy)
{
    enemies.removeOne(enemy);
    enemy->removeFromScene();
}

int GraphicsScene::getScreenWidth()
{
    return screenWidth;
}

int GraphicsScene::getScreenHeight()
{
    return screenHeight;
}

void GraphicsScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}

QGraphicsTextItem* GraphicsScene::getTextView()
{
    return textItem;
}

DebugFrame* GraphicsScene::getDebugFrame()
{
    return debugFrame;
}

void GraphicsScene::debugNextEnemy()
{
    int numberOfEnemies = enemies.size();
    numberOfDebuggedEnemy++;
    numberOfDebuggedEnemy %= numberOfEnemies;
    for(int i=0; i<numberOfEnemies; i++)
    {
        if(i==numberOfDebuggedEnemy)
            enemies.at(i)->selectToDebugInfo(true);
        else
            enemies.at(i)->selectToDebugInfo(false);
    }
}

Hero* GraphicsScene::getHero()
{
    return hero;
}

QList<Enemy*> GraphicsScene::getEnemies()
{
    return enemies;
}

QList<CircleItem*> GraphicsScene::getObstacles()
{
    return obstacles;
}

QList<CircleItem *> GraphicsScene::getCollidingObjects(bool withEnemies)
{
    QList<CircleItem*> collidingObjects;
    collidingObjects.append(obstacles);
    if(withEnemies)
    {
        foreach (Enemy* enemy, enemies)
            collidingObjects.append(enemy);
    }
    collidingObjects.append(hero);

    return collidingObjects;
}

 void GraphicsScene::createTextItems()
 {
     textItem = new QGraphicsTextItem();
     textItem->setPos(7*screenWidth/8, screenHeight-100);
     textItem->setHtml("Debug info");
     QFont font;
     font.setPointSize(10);
     textItem->setFont(font);
#ifdef DEBUG_GAME
     addItem(textItem);
#endif
     debugFrame = new DebugFrame(textItem);

     pointsFrame = new QGraphicsTextItem();
     pointsFrame->setPos(screenWidth-100, 10);
     pointsFrame->setHtml("Score: 0");
     addItem(pointsFrame);

     laserInfo = new QGraphicsTextItem();
     laserInfo->setPos(screenWidth-200, 30);
     laserInfo->setHtml("Laser ready to shoot");
     addItem(laserInfo);
 }

void GraphicsScene::createEnemies(int numberOfEnemies)
{
    for(int i=0; i<numberOfEnemies; i++)
    {
        Enemy* enemy = Enemy::createRandomEnemy(this, screenWidth, screenHeight);

#ifdef DEBUG_GAME
        if(i==0)
        {
            enemy->selectToDebugInfo(true);
        }
#endif
        enemies.append(enemy);
    }
}

void GraphicsScene::createObstacles()
{
    Vehicle* obstacle1 = new Vehicle(screenWidth/6, screenHeight/8, 100, this);
    Vehicle* obstacle2 = new Vehicle(screenWidth/6, 6*screenHeight/8, 100, this);
    Vehicle* obstacle3 = new Vehicle(4*screenWidth/6, screenHeight/7, 50, this);
    Vehicle* obstacle4 = new Vehicle(5*screenWidth/6, screenHeight/7, 120, this);
    Vehicle* obstacle5 = new Vehicle(4*screenWidth/6, 7*screenHeight/8, 100, this);
    Vehicle* obstacle6 = new Vehicle(2.5*screenWidth/6, 4*screenHeight/8, 140, this);

    obstacles.append(obstacle1);
    obstacles.append(obstacle2);
    obstacles.append(obstacle3);
    obstacles.append(obstacle4);
    obstacles.append(obstacle5);
    obstacles.append(obstacle6);
}

bool GraphicsScene::collideWithObjects(Vehicle *item, QPointF translationVector, bool enemy)
{
    CircleItem newCircle = getCircleAfterTranslation(item, translationVector);
    return collideWithBorders(newCircle) || collideWithObjectsInScene(item, newCircle, enemy);
}


bool GraphicsScene::collideWithBorders(QRectF rect)
{
    return (rect.left() < 0
            || rect.right() > screenWidth
            || rect.top() < 0
            || rect.bottom() > screenHeight);
}

bool GraphicsScene::collideWithBorders(CircleItem &circle)
{
    return (circle.x()-circle.radius() < 0
            || circle.x()+circle.radius() > screenWidth
            || circle.y()-circle.radius() < 0
            || circle.y()+circle.radius() > screenHeight);

}


bool GraphicsScene::collideWithObjectsInScene(Vehicle* item, CircleItem circle, bool enemy)
{
    bool collide = false;

    foreach (CircleItem* otherItem, getCollidingObjects())
    {
        if(otherItem == item)
            continue;

        double xDistanceBetweenCenters = std::fabs(circle.x() - otherItem->x());
        double yDistanceBetweenCenters = std::fabs(circle.y() - otherItem->y());

        double distanceBetweenCentersSquared = xDistanceBetweenCenters*xDistanceBetweenCenters + yDistanceBetweenCenters*yDistanceBetweenCenters;
        double radiusSum = circle.radius() + otherItem->radius();
        collide = (distanceBetweenCentersSquared < radiusSum*radiusSum );

        if(collide)
        {
            if(otherItem == hero && enemy)
            {
                endOfGame = true;
                showEndScreen();
            }
            return true;
        }
    }
    return false;
}


CircleItem GraphicsScene::getCircleAfterTranslation(Vehicle *item, QPointF translationVector)
{
    QPointF newCenter(item->x()+translationVector.x(), item->y()+translationVector.y());
    CircleItem newCircle(newCenter.x(), newCenter.y(), item->radius());
    return newCircle;
}
