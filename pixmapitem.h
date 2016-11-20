#ifndef __PIXMAPITEM__H__
#define __PIXMAPITEM__H__

#include <QtWidgets/QGraphicsObject>
#include <QGraphicsScene>

class GraphicsScene;

class PixmapItem : public QGraphicsObject
{
public:
    PixmapItem(const QString &fileName, GraphicsScene *scene);
    QSizeF size() const;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;
private:
    QPixmap pix;

protected:
    GraphicsScene *scene;

};

#endif //__PIXMAPITEM__H__
