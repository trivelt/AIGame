#include "pixmapitem.h"
#include "graphicsscene.h"
#include "logger.h"

#include <QPainter>
#include <QDebug>

PixmapItem::PixmapItem(const QString &fileName, GraphicsScene *scene) : QGraphicsObject()
{
    scene->addItem(this);
    this->scene = scene;

    pix  = QPixmap(QStringLiteral(":/") + fileName);
    Logger::log("Creating new PixMapItem from file '" + fileName + "', size=" +
            QString::number(pix.width()) + "x" + QString::number(pix.height()));
}

QSizeF PixmapItem::size() const
{
    return pix.size();
}

QRectF PixmapItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), pix.size());
}

void PixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pix);
}


