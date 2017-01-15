#ifndef DEBUGFRAME_H
#define DEBUGFRAME_H

#define DEBUG_GAME

#include <QGraphicsTextItem>
#include <QVector2D>

class DebugFrame
{
public:
    DebugFrame(QGraphicsTextItem* textItem);
    static bool debugMode();
    static void turnDebugMode();
    static void showFeelerLines();
    static bool feelerLines();

    void setHeroPosition(double x, double y);
    void setMousePosition(QPointF position);
    void setAgentTargetVector(QVector2D vector);
    void setDebugText(QString text);

private:
    void updateTextItem();
    QGraphicsTextItem* textItem;
    int updateCounter;

    QPointF heroPosition;
    QPointF mousePosition;
    QVector2D targetVector;
    QString debugText;

    static bool sDebugModeTurned;
    static bool sFeelerLines;

};

#endif // DEBUGFRAME_H
