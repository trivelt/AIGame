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
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    hero = new Hero(this);
    hero->setPos(0,0);

    enemy1 = new Enemy(this);
    enemy1->setPos(0,200);

    QGraphicsRectItem* rect = new QGraphicsRectItem(screenWidth/6, screenHeight/9, 300, 80);
    rect->setBrush(Qt::green);
    addItem(rect);

    QGraphicsRectItem* rect2 = new QGraphicsRectItem(screenWidth/6, 7*screenHeight/9, 300, 80);
    rect2->setBrush(Qt::green);
    addItem(rect2);

    textItem = new QGraphicsTextItem();
    textItem->setPos(screenWidth/2, screenHeight-80);
    textItem->setHtml("TEST 123");
    QFont font;
    font.setPointSize(20);
    textItem->setFont(font);
    addItem(textItem);

    laser = new Laser(this);
}

GraphicsScene::~GraphicsScene()
{
    delete hero;
    hero = nullptr;
    delete enemy1;
    enemy1 = nullptr;
}

void GraphicsScene::setupScene()
{
    QTimer::singleShot(100, enemy1, SLOT(updateEnemy()));
}

void GraphicsScene::clearScene()
{
}

void GraphicsScene::processHeroMove(QKeyEvent *event)
{
    hero->processKeyEvent(event);
}

void GraphicsScene::processLaserShot(QMouseEvent *event)
{
    laser->shot(event);
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

bool GraphicsScene::collideWithObjects(PixmapItem *item, QPoint translationVector)
{
    QRect newRect = getRectAfterTranslation(item, translationVector);
    return collideWithBorders(newRect) || collideWithObjectsInScene(item, newRect);
}

bool GraphicsScene::collideWithBorders(QRect rect)
{
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    return (rect.left() < 0
            || rect.right() > screenGeometry.width()
            || rect.top() < 0
            || rect.bottom() > screenGeometry.height());
}

bool GraphicsScene::collideWithObjectsInScene(PixmapItem* item, QRect rect)
{
    bool collide = false;

    foreach (QGraphicsItem* otherItem, items())
    {
        if(otherItem == item || otherItem == textItem)
            continue;
        QRectF otherRect = otherItem->sceneBoundingRect();

        collide = !(otherRect.left() > rect.right()
                    || otherRect.right() < rect.left()
                    || otherRect.top() > rect.bottom()
                    || otherRect.bottom() < rect.top());
        if(collide)
            return true;
    }
    return false;
}

QRect GraphicsScene::getRectAfterTranslation(PixmapItem *item, QPoint translationVector)
{
    QSizeF itemSize = item->size();
    QPointF itemPos = item->pos();
    int translationX = translationVector.x();
    int translationY = translationVector.y();

    int itemLeft = itemPos.x() + translationX;
    int itemTop = itemPos.y() + translationY;

    QRect newRect;
    newRect.setLeft(itemLeft);
    newRect.setTop(itemTop);
    newRect.setRight(itemLeft+itemSize.width());
    newRect.setBottom(itemTop+itemSize.height());

    return newRect;
}
