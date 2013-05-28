#ifndef QGRAPHICSTESTITEM_H
#define QGRAPHICSTESTITEM_H

#include <QGraphicsItem>
#include <QtGui>
#include <CentralView.h>

//const QColor genColor(int alpha = 255)
//{
//    int r = qrand() % 0xFF;
//    int g = qrand() % 0xFF;
//    int b = qrand() % 0xFF;

//    return QColor(r, g, b, alpha);
//}

#define OPWIDTH 5

template <typename GraphicsBase>
class TstGraphicsItem : public GraphicsBase {
public:
    TstGraphicsItem(bool useShadowItem = true, bool useBoundingRegion = true);
    virtual ~TstGraphicsItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QPainterPath shape() const;
    virtual QRectF boundingRect() const;
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    MainScene *castedScene();
    static QColor genColor();

protected:
    QGraphicsPathItem *shadowItem() {return mShadowItem;}
    QGraphicsPathItem *shadowBoundingRegion() {return mBoundingRegion;}

private:
    void updateBoundingRegion();

private:
    QGraphicsPathItem *mShadowItem;
    QGraphicsPathItem *mBoundingRegion;

};

template <typename GraphicsBase>
TstGraphicsItem<GraphicsBase>::TstGraphicsItem(bool useShadowItem, bool useBoundingRegion)
{
    qsrand(QTime::currentTime().msec());

    this->setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemSendsGeometryChanges
             | QGraphicsItem::ItemSendsScenePositionChanges);

    QColor brushColor = this->genColor();
    QColor penColor = this->genColor();

    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(penColor);

    int alpha = 0x88;
    brushColor.setAlpha(alpha);
    penColor.setAlpha(alpha);
    pen.setColor(penColor);

    if (useShadowItem) {
        mShadowItem = new QGraphicsPathItem();
        QPainterPath pth;
        pth.addRect(this->boundingRect());
        mShadowItem->setPath(pth);
        mShadowItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
        mShadowItem->setFlag(QGraphicsItem::ItemIsMovable, false);
        mShadowItem->setPen(pen);
        mShadowItem->setBrush(brushColor);
    }

    if (useBoundingRegion) {
        mBoundingRegion = new QGraphicsPathItem;
        mBoundingRegion->setFlag(QGraphicsItem::ItemIsSelectable, false);
        mBoundingRegion->setFlag(QGraphicsItem::ItemIsMovable, false);
        penColor.setAlpha(0x88);
        pen.setColor(penColor);
        mBoundingRegion->setPen(pen);
        brushColor.setAlpha(0x22);
        mBoundingRegion->setBrush(brushColor);
    }
}

template<typename GraphicsBase>
TstGraphicsItem<GraphicsBase>::~TstGraphicsItem()
{
    if (!this->scene()) {
        delete mShadowItem;
        delete mBoundingRegion;
    }
}

template<typename GraphicsBase>
void TstGraphicsItem<GraphicsBase>::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsBase::paint(painter, option, widget);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    painter->drawEllipse(this->transformOriginPoint(), OPWIDTH, OPWIDTH);
    painter->restore();
}

template<typename GraphicsBase>
QPainterPath TstGraphicsItem<GraphicsBase>::shape() const
{
    return QPainterPath();
}

template<typename GraphicsBase>
QRectF TstGraphicsItem<GraphicsBase>::boundingRect() const
{
    return QRectF();
}

template<typename GraphicsBase>
QVariant TstGraphicsItem<GraphicsBase>::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (static_cast<int>(change)) {
    case QGraphicsItem::ItemTransformHasChanged : {
        castedScene()->notifyTransformed(value.value<QTransform>());
        if (mBoundingRegion) {
            this->updateBoundingRegion();
        }
    } break;
    case QGraphicsItem::ItemPositionHasChanged : {
        if (mShadowItem) {
            mShadowItem->setPos(value.toPointF());
        }
        if (mBoundingRegion) {
            this->updateBoundingRegion();
        }
        castedScene()->notifyMoved(value.toPointF());
    } break;
    case QGraphicsItem::ItemTransformOriginPointHasChanged : {
        castedScene()->notifyOrginPointChanged(value.toPointF());
        if (mBoundingRegion) {
            this->updateBoundingRegion();
        }
    } break;
    case QGraphicsItem::ItemRotationHasChanged : {
        castedScene()->notifyRotated(value.toInt());
        if (mBoundingRegion) {
            this->updateBoundingRegion();
        }
    } break;
    case QGraphicsItem::ItemVisibleHasChanged : {
        if (mShadowItem) {
            QPainterPath pth;
            pth.addRect(boundingRect());
            mShadowItem->setPath(pth);
            mShadowItem->setVisible(value.toBool());
        }
        if (mBoundingRegion) {
            this->updateBoundingRegion();
            mBoundingRegion->setVisible(value.toBool());
        }
    } break;
    case QGraphicsItem::ItemSceneHasChanged : {
        if (this->scene()) {
            if (mShadowItem) {
                this->scene()->addItem(mShadowItem);
                mShadowItem->stackBefore(this);
            }
            if (mBoundingRegion) {
                this->scene()->addItem(mBoundingRegion);
            }
        } else if (mShadowItem) {
            mShadowItem->setParentItem(0);
        }
    } break;
    case QGraphicsItem::ItemZValueHasChanged : {
        if (mShadowItem) {
            mShadowItem->stackBefore(this);
        }
    } break;
    }

    return QGraphicsItem::itemChange(change, value);
}

template<typename GraphicsBase>
MainScene *TstGraphicsItem<GraphicsBase>::castedScene()
{
    return static_cast<MainScene*>(this->scene());
}

template<typename GraphicsBase>
QColor TstGraphicsItem<GraphicsBase>::genColor()
{
    int r = qrand() % 0xFF;
    int g = qrand() % 0xFF;
    int b = qrand() % 0xFF;

    return QColor(r, g, b);
}

template<typename GraphicsBase>
void TstGraphicsItem<GraphicsBase>::updateBoundingRegion()
{
    QPainterPath regionPath;
    regionPath.addRect(this->boundingRegion(this->sceneTransform()).boundingRect());
    mBoundingRegion->setPath(regionPath);
}

class GraphicsPathTstItem : public TstGraphicsItem<QGraphicsPathItem>
{
public:
    GraphicsPathTstItem();

    QPainterPath shape() const;
    QRectF boundingRect() const;
};

#endif // QGRAPHICSTESTITEM_H
