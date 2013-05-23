#ifndef QGRAPHICSTESTITEM_H
#define QGRAPHICSTESTITEM_H

#include <QGraphicsItem>
#include <QtGui>

class GraphicsTestItem : public QObject,  public QGraphicsPathItem
{
    Q_OBJECT

public:
    explicit GraphicsTestItem();
    ~GraphicsTestItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

signals:
    void transformChanged(const QTransform &pNewTransform);
    void positionChanged(const QPointF &pNewPositon);
    void transformOriginPointChanged(const QPointF &newPoint);
    void rotationChanged(int newAngle);
    
private:
    QGraphicsPathItem *mShadowItem;

    
};

#endif // QGRAPHICSTESTITEM_H
