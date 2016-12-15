#include "graphicsscene.h"
#include "logger.h"
#include "utils.h"

#include <QTimer>
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>

GraphicsScene::GraphicsScene(int x, int y, int width, int height)
    : QGraphicsScene(x , y, width, height)
{    
    endOfGame = false;
    score = 0;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    screenWidth = screenGeometry.width();
    screenHeight = screenGeometry.height();

    hero = new Hero(this);
    hero->setPos(0,0);

    createEnemies();
    createCollidingObjects();
    laser = new Laser(this);
    createTextItems();

}

GraphicsScene::~GraphicsScene()
{
    delete hero;
    hero = nullptr;

    foreach (Enemy* enemy, enemies) {
        enemies.removeOne(enemy);
        delete enemy;
    }
}

void GraphicsScene::setupScene()
{
    updateScene();
}

void GraphicsScene::updateScene()
{
    if(endOfGame)
        return;

    foreach (Enemy* enemy, enemies) {
        enemy->updateEnemy();
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
    addItem(backgroundRect);

    QGraphicsTextItem* endText = new QGraphicsTextItem();
    endText->setPos(screenWidth*0.35, screenHeight*0.3);
    QFont font;
    font.setPointSize(20);
    endText->setFont(font);
    endText->setHtml("<h1>GAME OVER</h1><br /> <br />&nbsp;&nbsp;&nbsp;Your score: " + QString::number(score) + " points");
    addItem(endText);
}

void GraphicsScene::processHeroMove(QKeyEvent *event)
{
    if(!endOfGame)
        hero->processKeyEvent(event);
}

void GraphicsScene::processLaserShot(QMouseEvent *event)
{
    if(!endOfGame)
        laser->shot(event);
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

Hero* GraphicsScene::getHero()
{
    return hero;
}

QList<Enemy*> GraphicsScene::getEnemies()
{
    return enemies;
}

QList<QGraphicsItem*> GraphicsScene::getCollidingObjects()
{
    return collidingObjects;
}

 void GraphicsScene::createTextItems()
 {
     textItem = new QGraphicsTextItem();
     textItem->setPos(screenWidth/2, screenHeight-80);
     textItem->setHtml("TEST 123");
     QFont font;
     font.setPointSize(20);
     textItem->setFont(font);
     addItem(textItem);

     pointsFrame = new QGraphicsTextItem();
     pointsFrame->setPos(screenWidth-100, 10);
     pointsFrame->setHtml("Score: 0");
     addItem(pointsFrame);

     laserInfo = new QGraphicsTextItem();
     laserInfo->setPos(screenWidth-200, 30);
     laserInfo->setHtml("Laser ready to shoot");
     addItem(laserInfo);
 }

void GraphicsScene::createEnemies()
{
    Enemy *enemy1 = new Enemy(this);
    enemy1->setPos(0,200);

    Enemy *enemy2 = new Enemy(this);
    enemy2->setPos(600,300);

    enemies.append(enemy1);
    enemies.append(enemy2);
}

void GraphicsScene::createCollidingObjects()
{
    QGraphicsRectItem* rect = new QGraphicsRectItem(screenWidth/6, screenHeight/9, 300, 80);
    rect->setBrush(Qt::green);
    addItem(rect);

    QGraphicsRectItem* rect2 = new QGraphicsRectItem(screenWidth/6, 7*screenHeight/9, 300, 80);
    rect2->setBrush(Qt::green);
    addItem(rect2);

    collidingObjects.append(rect);
    collidingObjects.append(rect2);
}

bool GraphicsScene::collideWithObjects(PixmapItem *item, QPointF translationVector, bool enemy)
{
    QRectF newRect = getRectAfterTranslation(item, translationVector);
    return collideWithBorders(newRect) || collideWithObjectsInScene(item, newRect, enemy);
}

bool GraphicsScene::collideWithBorders(QRectF rect)
{
    return (rect.left() < 0
            || rect.right() > screenWidth
            || rect.top() < 0
            || rect.bottom() > screenHeight);
}

bool GraphicsScene::collideWithObjectsInScene(PixmapItem* item, QRectF rect, bool enemy)
{
    bool collide = false;

    foreach (QGraphicsItem* otherItem, items())
    {
        if(otherItem == item || otherItem == textItem
                || otherItem == pointsFrame || otherItem == laserInfo)
            continue;
        QRectF otherRect = otherItem->sceneBoundingRect();

        collide = !(otherRect.left() > rect.right()
                    || otherRect.right() < rect.left()
                    || otherRect.top() > rect.bottom()
                    || otherRect.bottom() < rect.top());
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

QRectF GraphicsScene::getRectAfterTranslation(PixmapItem *item, QPointF translationVector)
{
    QSizeF itemSize = item->size();
    QPointF itemPos = item->pos();
    double translationX = translationVector.x();
    double translationY = translationVector.y();

    double itemLeft = itemPos.x() + translationX;
    double itemTop = itemPos.y() + translationY;

    QRectF newRect;
    newRect.setLeft(itemLeft);
    newRect.setTop(itemTop);
    newRect.setRight(itemLeft+itemSize.width());
    newRect.setBottom(itemTop+itemSize.height());

    return newRect;
}
