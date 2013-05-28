#include "CentralView.h"

#include <QtGui>
#include <GraphicsTestItem.h>

#include  "TestDock.h"

const int gridLength = 1500;
const int gridShot = 100;
const int indentSize = 5;

CentralView::CentralView(QWidget *parent) :
    QWidget(parent)
  , mScene(new MainScene(this))
  , mView(new GraphView(this))
  , mRubberBandDragModeButton(0)
  , mHandDragModeButton(0)
{
    setupUi();
    connect(mScene, SIGNAL(selectionChanged(QList<QGraphicsItem*>)), this, SLOT(slot_sceneSelectionChanged(QList<QGraphicsItem*>)));
    connect(mRubberBandDragModeButton, SIGNAL(clicked()), this, SLOT(changeRubberBandDragMode()));
    connect(mHandDragModeButton, SIGNAL(clicked()), this, SLOT(changeRubberBandDragMode()));

    connect(mScene, SIGNAL(transformChanged(QTransform)), this, SIGNAL(signal_ItemTransformChanged(QTransform)));
    connect(mScene, SIGNAL(positionChanged(QPointF)), this, SIGNAL(signal_ItemPositionChanged(QPointF)));
    connect(mScene, SIGNAL(transformOriginPointChanged(QPointF)), this , SIGNAL(signal_ItemTransformOriginPointChanged(QPointF)));
    connect(mScene, SIGNAL(rotationChanged(int)), this, SIGNAL(signal_ItemRotationChanged(int)));

    mRubberBandDragModeButton->click();
}

QSize CentralView::sizeHint() const
{
    return QSize(800, 600);
}

QRectF CentralView::visibleSceneRect() const
{
    QPointF topLeft = mView->mapToScene(QPoint(0, 0));
    QPointF bottomRight = mView->mapToScene(QPoint(mView->width(), mView->height()));

    return QRectF(topLeft, bottomRight);
}

//srand((unsigned)time(0));
//    int random_integer;
//    int lowest=1, highest=10;
//    int range=(highest-lowest)+1;
//    for(int index=0; index<20; index++){
//        random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));
//        cout << random_integer << endl;
//    }

void CentralView::addItem()
{
    qDebug() << "add item";
    qsrand(QTime::currentTime().msec());

    GraphicsPathTstItem *nextItem = new GraphicsPathTstItem;
    QPainterPath path;
    path.addRect(0, 0, 150, 100);
    nextItem->setPath(path);


//    connect(nextItem, SIGNAL(positionChanged(QPointF)), this, SIGNAL(signal_ItemPositionChanged(QPointF)));
//    connect(nextItem, SIGNAL(transformChanged(QTransform)), this, SIGNAL(signal_ItemTransformChanged(QTransform)));
//    connect(nextItem, SIGNAL(transformOriginPointChanged(QPointF)), this, SIGNAL(signal_ItemTransformOriginPointChanged(QPointF)));
//    connect(nextItem, SIGNAL(rotationChanged(int)), this, SIGNAL(signal_ItemRotationChanged(int)));

    mScene->addItem(nextItem);
    nextItem->setVisible(true);

//    QRectF visibRect = visibleSceneRect();
//    int itemsCount = 4000;

//    qsrand(QTime::currentTime().msec());

//    int xRange = visibRect.width();
//    int yRange = visibRect.height();

//    int xOffset = visibRect.x();
//    int yOffset = visibRect.y();

//    for (int i = 0; i < itemsCount; i++) {
//        QPointF placePoint = QPointF(xOffset + static_cast<qreal>(rand() % xRange)
//                                     ,yOffset + static_cast<qreal>(rand() % yRange));

//        QPixmap pixmap("/home/ilia/Documents/sample.png");
//        if (!pixmap.isNull()) {
//            QGraphicsPixmapItem *pix = mScene->addPixmap(pixmap);
//            pix->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
//            pix->setPos(placePoint);
//            pix->setVisible(true);
//        }
//        qDebug() << "Processing item no" << i;
//    }
}

void CentralView::slot_sceneSelectionChanged(QList<QGraphicsItem *> pSelected)
{
    switch (pSelected.count()) {
    case 0 :
        break;
    case 1 : {
        QGraphicsItem *curItem = pSelected.first();
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
//        qDebug() << "items bounding rect" << curItem->boundingRect();
//        qDebug() << "Item's bounding region" << curItem->boundingRegion(curItem->sceneTransform());
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
        QGraphicsItem *curItem = selectedItems.first();
        QRectF ownRect = curItem->boundingRect();
        QPointF center = ownRect.center();
        emit signal_sendCenterCoords(center);
       } break;
    default :
        break;
    }
}

void CentralView::changeRubberBandDragMode()
{
    if (sender() == mRubberBandDragModeButton) {
        mView->setDragMode(QGraphicsView::RubberBandDrag);
    } else if (sender() == mHandDragModeButton) {
        mView->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}

void CentralView::startTest(const requestContent &req)
{
    if (!req.numItems || req.itemType.isNull()) {
        return;
    }

    QRectF visibRect = visibleSceneRect();
    int itemsCount = req.numItems;

    qsrand(QTime::currentTime().msec());

    int xRange = visibRect.width();
    int yRange = visibRect.height();

    int xOffset = visibRect.x();
    int yOffset = visibRect.y();

    for (int i = 0; i < itemsCount; i++) {
        QPointF placePoint = QPointF(xOffset + static_cast<qreal>(rand() % xRange)
                                     ,yOffset + static_cast<qreal>(rand() % yRange));

        if (req.itemType == PIX_ITEM) {
            QPixmap pixmap("/home/ilia/Documents/sample.png");
            if (!pixmap.isNull()) {
                QGraphicsPixmapItem *pix = mScene->addPixmap(pixmap);
                pix->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                pix->setPos(placePoint);
                pix->setVisible(true);
            }
        } else if (req.itemType == PATH_ITEM) {
            GraphicsPathTstItem *nextItem = new GraphicsPathTstItem;
            QPainterPath path;
            path.addRect(0, 0, 25, 15);
            nextItem->setPath(path);

            mScene->addItem(nextItem);
            nextItem->setVisible(true);
            nextItem->setPos(placePoint);
        }
        qDebug() << "Processing item no" << i;
    }
}

void CentralView::setupUi()
{
    mView->setScene(mScene);


    QVBoxLayout *mainLayer = new QVBoxLayout;

    QHBoxLayout *buttonLayer = new QHBoxLayout;
    mRubberBandDragModeButton = new QPushButton("Rubber drag");
    mHandDragModeButton = new QPushButton("Hand drag");
    buttonLayer->addWidget(mRubberBandDragModeButton);
    buttonLayer->addWidget(mHandDragModeButton);
    buttonLayer->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    mainLayer->addLayout(buttonLayer, 0);
    mainLayer->addWidget(mView, 1);

    setLayout(mainLayer);
}

GraphView::GraphView(QWidget *parent)
    : QGraphicsView(parent)
{
//    setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
    setTransformationAnchor(AnchorViewCenter);
}

QSize GraphView::sizeHint() const
{
    if (scene()) {
        return scene()->sceneRect().size().toSize();
    }

    return QGraphicsView::sizeHint();
}

MainScene::MainScene(QObject *parent) :
    QGraphicsScene(parent)
{
    addCoords();
    addScale();

    connect(this, SIGNAL(selectionChanged()), this, SLOT(slot_selectionChanged()));
}

void MainScene::notifyTransformed(const QTransform &pNewTransform, QGraphicsItem *)
{
    DEF_IF_COUNT_SCENE(, emit transformChanged(pNewTransform), )
}

void MainScene::notifyMoved(const QPointF &pNewPositon, QGraphicsItem *)
{
    DEF_IF_COUNT_SCENE(, emit positionChanged(pNewPositon), )
}

void MainScene::notifyOrginPointChanged(const QPointF &newPoint, QGraphicsItem *)
{
    DEF_IF_COUNT_SCENE(, emit transformOriginPointChanged(newPoint), )
}

void MainScene::notifyRotated(int newAngle, QGraphicsItem *)
{
    DEF_IF_COUNT_SCENE(, emit rotationChanged(newAngle), )
}

void MainScene::slot_selectionChanged()
{
    emit selectionChanged(selectedItems());
}

void MainScene::addCoords()
{
    QPen drawPen;
    drawPen.setBrush(Qt::darkGray);
    drawPen.setWidthF(2.0);

    QLineF hLine(0, 0, gridLength, 0);
    QLineF vLine(0, 0, 0, gridLength);

    addLine(hLine, drawPen);
    addLine(vLine, drawPen);

    drawPen.setStyle(Qt::DashDotLine);

    QLineF hDashLine(-gridLength, 0, 0, 0);
    QLineF vDashLine(0, -gridLength, 0, 0);

    addLine(hDashLine, drawPen);
    addLine(vDashLine, drawPen);
}

void MainScene::addScale()
{
    QPen gridPen;
    gridPen.setBrush(Qt::lightGray);
    gridPen.setWidthF(1.0);

    QPen scalePen;
    scalePen.setBrush(Qt::darkGray);
    scalePen.setWidthF(3.0);

    for (int i = -gridLength; i <= gridLength; i += gridShot) {
        if (!i) {
            continue;
        }
        QLineF hLine(-gridLength, i, gridLength, i);
        QLineF vLine(i, -gridLength, i, gridLength);

        addLine(hLine, gridPen);
        addLine(vLine, gridPen);

        int textX = i;
        int textY = i;

        QGraphicsTextItem *scaleHText = addText(QString::number(i));
        scaleHText->setPos(textX, 0);
        QGraphicsTextItem *scaleVText = addText(QString::number(i));
        scaleVText->setPos(0, textY);

        QLineF hIndentLine(textX, -indentSize / 2, textX, indentSize / 2);
        QLineF vIndentLine(-indentSize / 2, textY, indentSize / 2, textY);

        addLine(hIndentLine, scalePen);
        addLine(vIndentLine, scalePen);
    }

    addText("0");
}
