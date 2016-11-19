#include "graphicsscene.h"
#include "logger.h"
#include <QTimer>
#include "utils.h"
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>

GraphicsScene::GraphicsScene(int x, int y, int width, int height)
    : QGraphicsScene(x , y, width, height)
{    
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    kolko1 = new PixmapItem(QString("kolko1"));
    kolko1->setPos(0,0);
    addItem(kolko1);

    enemy1 = new PixmapItem(QString("kolko1"));
    enemy1->setPos(0,200);
    addItem(enemy1);

    QGraphicsRectItem* rect = new QGraphicsRectItem(300, 100, 300, 80);
    rect->setBrush(Qt::green);
    addItem(rect);

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
    delete kolko1;
    kolko1 = nullptr;
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
        QPointF positionOfHero = kolko1->pos();
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

void GraphicsScene::goDown()
{
    for(int i=0;i <10; i++)
    {
        if(!collideWithPoint(kolko1, QPoint(0, 1)))
        {

            QPointF posPoint = kolko1->pos();
            int yPos = posPoint.y();
            kolko1->setPos(posPoint.x(), yPos+1);
            textItem->setHtml("x=" + QString::number(posPoint.x()) + ", y=" + QString::number(yPos));
        }
        else
        {
            break;
        }
    }

}

void GraphicsScene::goUp()
{
    QPointF posPoint = kolko1->pos();
    int yPos = posPoint.y();
    kolko1->setPos(posPoint.x(), yPos-10);
    textItem->setHtml("x=" + QString::number(posPoint.x()) + ", y=" + QString::number(yPos));
}

void GraphicsScene::goRight()
{
    QPointF posPoint = kolko1->pos();
    int xPos = posPoint.x();
    kolko1->setPos(xPos+10,posPoint.y());
    textItem->setHtml("x=" + QString::number(xPos) + ", y=" + QString::number(posPoint.y()));
}

void GraphicsScene::goLeft()
{
    QPointF posPoint = kolko1->pos();
    int xPos = posPoint.x();
    kolko1->setPos(xPos-10,posPoint.y());
    textItem->setHtml("x=" + QString::number(xPos) + ", y=" + QString::number(posPoint.y()));
}

void GraphicsScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}

bool GraphicsScene::collideWithPoint(PixmapItem *item, QPoint translationVector)
{
    QPointF itemPos = item->pos();
    int translationX = translationVector.x();
    int translationY = translationVector.y();

    QSizeF itemSize = item->size();
    int itemWidth = itemSize.width();
    int itemHeight = itemSize.height();

    int itemLeft = itemPos.x() + translationX;
    int itemTop = itemPos.y() + translationY;
    int itemRight = itemPos.x() + itemWidth + translationX;
    int itemBottom = itemPos.y() + itemHeight + translationY;

    bool collide = false;

    foreach (QGraphicsItem* otherItem, items())
    {
        if(otherItem == item)
            continue;
        QRectF otherRect = otherItem->boundingRect();
        otherRect.translate(otherItem->pos());

        int otherLeft = otherRect.left();
        int otherTop = otherRect.top();
        int otherRight = otherRect.right();
        int otherBottom = otherRect.bottom();

        collide = !(otherLeft > itemRight
                    || otherRight < itemLeft
                    || otherTop > itemBottom
                    || otherBottom < itemTop);
        if(collide)
            return true;
    }
    return false;
}
