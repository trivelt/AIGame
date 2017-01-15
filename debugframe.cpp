#include "debugframe.h"
#include <QDebug>

DebugFrame::DebugFrame(QGraphicsTextItem *textItem)
{
    this->textItem = textItem;
    updateCounter = 0;
}

void DebugFrame::setHeroPosition(double x, double y)
{
    heroPosition.setX(x);
    heroPosition.setY(y);
    qDebug() << "Position set";
    updateTextItem();
}

void DebugFrame::setAgentTargetVector(QVector2D vector)
{
    targetVector = vector;
    updateCounter--;
    qDebug() << "counter = " << updateCounter;
    if(updateCounter <= 0)
    {
        updateTextItem();
        updateCounter = 50;
    }
}

void DebugFrame::updateTextItem()
{
    QString text= "Hero: " + QString::number(heroPosition.x(), 'f', 1) + ", " + QString::number(heroPosition.y(), 'f', 1);
    text += "<br />Agent target: " + QString::number(targetVector.x(), 'f', 1) + ", " + QString::number(targetVector.y(), 'f', 1);
    textItem->setHtml(text);
}
