#ifndef __PIXMAPITEM__H__
#define __PIXMAPITEM__H__

#include "graphicsscene.h"
#include <QtWidgets/QGraphicsObject>

class PixmapItem : public QGraphicsObject
{
public:
    PixmapItem(const QString &fileName, QGraphicsItem * parent = 0);
    PixmapItem(const QString &fileName, QGraphicsScene *scene);
    QSizeF size() const;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;
private:
    QPixmap pix;
};

#endif //__PIXMAPITEM__H__
