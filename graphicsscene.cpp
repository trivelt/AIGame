#include "graphicsscene.h"
#include "logger.h"
#include <QTimer>
#include "utils.h"
#include "hero.h"
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

    enemy1 = new PixmapItem(QString("enemy"), this);
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
    QTimer::singleShot(100, this, SLOT(updateScene()));
}

void GraphicsScene::updateScene()
{
    static bool yourTurn = false;
    yourTurn = !yourTurn;

    if(yourTurn)
    {
        QPointF positionOfHero = hero->pos();
        int xPosHero = positionOfHero.x();
        int yPosHero = positionOfHero.y();


        QPointF posPoint = enemy1->pos();
        int xPos = posPoint.x();
        int yPos = posPoint.y();
        if(xPos > xPosHero)
        {
            xPos--;
        }
        else if(xPos < xPosHero)
        {
            xPos++;
        }

        if(yPos > yPosHero)
        {
            yPos--;
        }
        else if(yPos < yPosHero)
        {
            yPos++;
        }

        enemy1->setPos(xPos, yPos);
    }

    QTimer::singleShot(10, this, SLOT(updateScene()));

}


void GraphicsScene::clearScene()
{

}

void GraphicsScene::processHeroMove(QKeyEvent *event)
{
    hero->processKeyEvent(event);
}

void GraphicsScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}

QGraphicsTextItem* GraphicsScene::getTextView()
{
    return textItem;
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
        if(otherItem == item)
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
    QPointF itemPos = item->pos();
    int translationX = translationVector.x();
    int translationY = translationVector.y();

    int itemLeft = itemPos.x() + translationX;
    int itemTop = itemPos.y() + translationY;

    QSizeF itemSize = item->size();
    int itemWidth = itemSize.width();
    int itemHeight = itemSize.height();

    QRect newRect(itemLeft, itemTop, itemWidth, itemHeight);
    return newRect;
}
