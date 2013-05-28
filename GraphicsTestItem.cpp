#include "GraphicsTestItem.h"

#include <QtGui>
#include "CentralView.h"

const QColor generateColor(int alpha = 255)
{
    int r = qrand() % 0xFF;
    int g = qrand() % 0xFF;
    int b = qrand() % 0xFF;

    return QColor(r, g, b, alpha);
}

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
