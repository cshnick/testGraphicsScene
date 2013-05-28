#include "GraphicsTestItem.h"

#include <QtGui>
#include "CentralView.h"

const int opWidth = 5;

GraphicsPathTstItem::GraphicsPathTstItem()
    : TstGraphicsItem<QGraphicsPathItem>()
{
    QColor penCol = shadowItem() ? shadowItem()->pen().color() : genColor();
    QColor brushColor = shadowItem() ? shadowItem()->brush().color() : genColor();

    penCol.setAlpha(0xFF);
    penCol.setAlpha(0xFF);

    setPen(QPen(penCol));
    setBrush(brushColor);
}

QPainterPath GraphicsPathTstItem::shape() const
{
    QPainterPath result;
    result.addPath(path());

    result.addEllipse(transformOriginPoint(), OPWIDTH, OPWIDTH);

    return result;
}

QRectF GraphicsPathTstItem::boundingRect() const
{
    QPainterPath result;
    result.addPath(path());
    result.addEllipse(transformOriginPoint(), OPWIDTH, OPWIDTH);

    return result.boundingRect();
}

GraphicsPixmapTstItem::GraphicsPixmapTstItem()
    : TstGraphicsItem<QGraphicsPixmapItem>()
{
}

QPainterPath GraphicsPixmapTstItem::shape() const
{
    QPainterPath result;
    result.addRect(0, 0, pixmap().width(), pixmap().height());

    result.addEllipse(transformOriginPoint(), OPWIDTH, OPWIDTH);

    return result;
}

QRectF GraphicsPixmapTstItem::boundingRect() const
{
    QPainterPath result;
    result.addRect(0, 0, pixmap().width(), pixmap().height());
    result.addEllipse(transformOriginPoint(), OPWIDTH, OPWIDTH);

    return result.boundingRect();
}


