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

GraphicsTestItem::GraphicsTestItem()
    : mShadowItem(0)
    , mBoundingRegion(0)
{
    qsrand(QTime::currentTime().msec());

    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemSendsGeometryChanges
             | QGraphicsItem::ItemSendsScenePositionChanges);

    QColor brushColor = generateColor();
    QColor penColor = generateColor();

    setBrush(brushColor);
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(penColor);
    setPen(pen);


    int alpha = 0x88;
    brushColor.setAlpha(alpha);
    penColor.setAlpha(alpha);
    pen.setColor(penColor);

    mShadowItem = new QGraphicsPathItem();
    mShadowItem->setPath(path());
    mShadowItem->setFlag(ItemIsSelectable, false);
    mShadowItem->setFlag(ItemIsMovable, false);
    mShadowItem->setPen(pen);
    mShadowItem->setBrush(brushColor);

    mBoundingRegion = new QGraphicsPathItem;
    mBoundingRegion->setFlag(ItemIsSelectable, false);
    mBoundingRegion->setFlag(ItemIsMovable, false);
    penColor.setAlpha(0x88);
    pen.setColor(penColor);
    mBoundingRegion->setPen(pen);
    brushColor.setAlpha(0x22);
    mBoundingRegion->setBrush(brushColor);
}

GraphicsTestItem::~GraphicsTestItem()
{
    if (!scene()) {
        delete mShadowItem;
        delete mBoundingRegion;
    }
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

QRectF GraphicsTestItem::boundingRect() const
{
    QPainterPath result;
    result.addPath(path());
    result.addEllipse(transformOriginPoint(), opWidth, opWidth);

    return result.boundingRect();
}

QVariant GraphicsTestItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (static_cast<int>(change)) {
    case ItemTransformHasChanged : {
        emit transformChanged(value.value<QTransform>());
        updateBoundingRegion();
    } break;
    case ItemPositionHasChanged : {
        mShadowItem->setPos(value.toPointF());
        updateBoundingRegion();
        emit positionChanged(value.toPointF());
    } break;
    case ItemTransformOriginPointHasChanged : {
        emit transformOriginPointChanged(value.toPointF());
        updateBoundingRegion();
    } break;
    case ItemRotationHasChanged : {
        emit rotationChanged(value.toInt());
        updateBoundingRegion();
    } break;
    case ItemVisibleHasChanged : {
        mShadowItem->setPath(path());
        mShadowItem->setVisible(value.toBool());
        updateBoundingRegion();
        mBoundingRegion->setVisible(value.toBool());
    } break;
    case ItemSceneHasChanged : {
        if (scene()) {
            scene()->addItem(mShadowItem);
            mShadowItem->stackBefore(this);
            scene()->addItem(mBoundingRegion);
        } else {
            mShadowItem->setParentItem(0);
        }
    } break;
    case ItemZValueHasChanged : {
        mShadowItem->stackBefore(this);
    } break;
    }

    return QGraphicsPathItem::itemChange(change, value);
}

void GraphicsTestItem::updateBoundingRegion()
{
    QPainterPath regionPath;
    regionPath.addRect(boundingRegion(sceneTransform()).boundingRect());
    mBoundingRegion->setPath(regionPath);
}
