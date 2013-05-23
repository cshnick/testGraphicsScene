#include "CentralView.h"

#include <QtGui>
#include <GraphicsTestItem.h>

CentralView::CentralView(QWidget *parent) :
    QGraphicsView(parent)
{
    mScene = new MainScene(this);
    setScene(mScene);

    connect(mScene, SIGNAL(selectionChanged(QList<GraphicsTestItem*>)), this, SLOT(slot_sceneSelectionChanged(QList<GraphicsTestItem*>)));

    setDragMode(RubberBandDrag);
}

QSize CentralView::sizeHint() const
{
    if (scene()) {
        return scene()->sceneRect().size().toSize();
    }

    return QGraphicsView::sizeHint();
}

void CentralView::addItem()
{
    qDebug() << "add item";
    GraphicsTestItem *nextItem = new GraphicsTestItem;
    QPainterPath path;
    path.addRect(0, 0, 150, 100);
    nextItem->setPath(path);

    connect(nextItem, SIGNAL(positionChanged(QPointF)), this, SIGNAL(signal_ItemPositionChanged(QPointF)));
    connect(nextItem, SIGNAL(transformChanged(QTransform)), this, SIGNAL(signal_ItemTransformChanged(QTransform)));
    connect(nextItem, SIGNAL(transformOriginPointChanged(QPointF)), this, SIGNAL(signal_ItemTransformOriginPointChanged(QPointF)));
    connect(nextItem, SIGNAL(rotationChanged(int)), this, SIGNAL(signal_ItemRotationChanged(int)));

    mScene->addItem(nextItem);
    nextItem->setVisible(true);
}

void CentralView::slot_sceneSelectionChanged(QList<GraphicsTestItem *> pSelected)
{
    switch (pSelected.count()) {
    case 0 :
        break;
    case 1 : {
        GraphicsTestItem *curItem = pSelected.first();
        emit (signal_ItemTransformChanged(curItem->transform()));
        emit (signal_ItemRotationChanged(curItem->rotation()));
        emit (signal_ItemTransformOriginPointChanged(curItem->transformOriginPoint()));
        emit (signal_ItemPositionChanged(curItem->pos()));

       } break;
    default :
        break;
    }
}

void CentralView::applyTransform(const QTransform &pTransform)
{
    QList<QGraphicsItem*> selectedItems = mScene->selectedItems();
    switch (selectedItems.count()) {
    case 0 :
        break;
    case 1 : {
        QGraphicsItem *curItem = selectedItems.first();
        curItem->setTransform(pTransform, false);
       } break;
    default :
        break;
    }
}

void CentralView::applyPosition(const QPointF &newPoint)
{
    QList<QGraphicsItem*> selectedItems = mScene->selectedItems();
    switch (selectedItems.count()) {
    case 0 :
        break;
    case 1 : {
        QGraphicsItem *curItem = selectedItems.first();
        curItem->setPos(newPoint);
       } break;
    default :
        break;
    }
}

void CentralView::applyTransformOriginPoint(const QPointF &newPoint)
{
    QList<QGraphicsItem*> selectedItems = mScene->selectedItems();
    switch (selectedItems.count()) {
    case 0 :
        break;
    case 1 : {
        QGraphicsItem *curItem = selectedItems.first();
        curItem->setTransformOriginPoint(newPoint);
       } break;
    default :
        break;
    }
}

void CentralView::applyNewAngle(int newAngle)
{
    QList<QGraphicsItem*> selectedItems = mScene->selectedItems();
    switch (selectedItems.count()) {
    case 0 :
        break;
    case 1 : {
        QGraphicsItem *curItem = selectedItems.first();
        curItem->setRotation(newAngle);
       } break;
    default :
        break;
    }
}

void CentralView::reactOnCenterCoordsRequest()
{
    QList<QGraphicsItem*> selectedItems = mScene->selectedItems();
    switch (selectedItems.count()) {
    case 0 :
        break;
    case 1 : {
        GraphicsTestItem *curItem = static_cast<GraphicsTestItem*>(selectedItems.first());
        QRectF ownRect = curItem->path().boundingRect();
        QPointF center = ownRect.center();
        emit signal_sendCenterCoords(center);
       } break;
    default :
        break;
    }
}

MainScene::MainScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 805, 605);
    addCoords();
    addScale();

    connect(this, SIGNAL(selectionChanged()), this, SLOT(slot_selectionChanged()));
}

void MainScene::slot_selectionChanged()
{
    QList<QGraphicsItem*> selItems = selectedItems();
    QList<GraphicsTestItem*> castItems;

    foreach (QGraphicsItem *nextItem, selItems) {
        GraphicsTestItem *nGTi = static_cast<GraphicsTestItem*>(nextItem);
        castItems.append(nGTi);
    }

    emit selectionChanged(castItems);
}

void MainScene::addCoords()
{
    QPen drawPen;
    drawPen.setBrush(Qt::darkGray);
    drawPen.setWidthF(2.0);



    QLineF hLine(0, 0, width(), 0);
    QLineF vLine(0, 0, 0, height());

    addLine(hLine, drawPen);
    addLine(vLine, drawPen);

    addText("0");
}

void MainScene::addScale()
{
    int shot = 100;

    QPen gridPen;
    gridPen.setBrush(Qt::lightGray);
    gridPen.setWidthF(1.0);

    QPen scalePen;
    scalePen.setBrush(Qt::darkGray);
    scalePen.setWidthF(2.0);


    int mi = qMax(width(), height());
    for (int i = shot; i <= mi; i += shot) {
        QLineF hLine(0, i, width(), i);
        QLineF vLine(i, 0, i, height());

        addLine(hLine, gridPen);
        addLine(vLine, gridPen);
    }
}
