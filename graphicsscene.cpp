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

    textItem = new QGraphicsTextItem();
    textItem->setPos(screenWidth/2, screenHeight-80);
    textItem->setHtml("TEST 123");
    QFont font;
    font.setPointSize(20);
    textItem->setFont(font);
    addItem(textItem);

//    PixmapItem *backgroundItem = new PixmapItem(QString("background"));
//    backgroundItem->setZValue(1);
//    backgroundItem->setPos(0,0);
//    addItem(backgroundItem);
}

GraphicsScene::~GraphicsScene()
{
    delete kolko1;
    kolko1 = nullptr;
}

void GraphicsScene::setupScene()
{
    QTimer::singleShot(100, this, SLOT(updateSc()));
}


void GraphicsScene::updateScene()
{
//    Logger::log("Updating scene");
    QPointF posPoint = kolko1->pos();
    int xPos = posPoint.x();
    kolko1->setPos(xPos+10,posPoint.y());
    textItem->setHtml("x=" + QString::number(xPos) + ", y=" + QString::number(posPoint.y()));
}

void GraphicsScene::updateSc()
{
    static bool yourTurn = false;
    yourTurn = !yourTurn;

    if(yourTurn)
    {
//    Logger::log("Updating scene");
//    QPointF posPoint = kolko1->pos();
//    int yPos = posPoint.y();
//    for(int i=0;i<20;i++)
//    {
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
//        Utils::sleep(10);
    }
//    kolko1->setPos(posPoint.x(), yPos+5);
//    textItem->setHtml("x=" + QString::number(posPoint.x()) + ", y=" + QString::number(yPos));
    QTimer::singleShot(10, this, SLOT(updateSc()));

}


void GraphicsScene::clearScene()
{

}

void GraphicsScene::goDown()
{
    QPointF posPoint = kolko1->pos();
    int yPos = posPoint.y();
    kolko1->setPos(posPoint.x(), yPos+10);
    textItem->setHtml("x=" + QString::number(posPoint.x()) + ", y=" + QString::number(yPos));
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
