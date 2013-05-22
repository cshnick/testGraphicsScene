#include "GraphicsTestItem.h"

#include <QtGui>
#include "CentralView.h"

const int opWidth = 5;

GraphicsTestItem::GraphicsTestItem()
{
    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemSendsGeometryChanges
             | QGraphicsItem::ItemSendsScenePositionChanges);



    setBrush(Qt::blue);
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(Qt::yellow);
    setPen(pen);
}

void GraphicsTestItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QGraphicsPathItem::paint(painter, option, widget);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    painter->drawEllipse(transformOriginPoint(), opWidth, opWidth);
    painter->restore();
}

QPainterPath GraphicsTestItem::shape() const
{
    QPainterPath result;
    result.addPath(path());
//    result.addRect(boundingRect());
    result.addEllipse(transformOriginPoint(), opWidth, opWidth);

    return result;
}

QVariant GraphicsTestItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (static_cast<int>(change)) {
    case ItemTransformHasChanged : {
        emit transformChanged(value.value<QTransform>());
    } break;
    case ItemPositionHasChanged : {
        emit positionChanged(value.toPointF());
    } break;
    case ItemTransformOriginPointHasChanged : {
        emit transformOriginPointChanged(value.toPointF());
    } break;
    case ItemRotationHasChanged : {
        emit rotationChanged(value.toInt());
    } break;

    }

    return QGraphicsPathItem::itemChange(change, value);
}
