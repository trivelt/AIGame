#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>


class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);

protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // GRAPHICSVIEW_H
