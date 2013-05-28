#ifndef CENTRALVIEW_H
#define CENTRALVIEW_H

#include <QGraphicsView>
#include <QtGui>

#define DEF_IF_COUNT_SCENE(action0, action1, actionMore)       \
QList<QGraphicsItem*> si(selectedItems());                     \
switch (si.count()) {                                          \
case 0 :                                                       \
    action0;                                                   \
    break;                                                     \
case 1 : {                                                     \
    action1;                                                   \
   } break;                                                    \
default :                                                      \
    actionMore;                                                \
    break;                                                     \
}                                                              \

class MainScene;
class GraphicsTestItem;
class GraphView;
class requestContent;

class CentralView : public QWidget
{
    Q_OBJECT
public:
    explicit CentralView(QWidget *parent = 0);
    QSize sizeHint() const;
    QRectF visibleSceneRect() const;

signals:
    void signal_ItemTransformChanged(const QTransform &pTransform);
    void signal_ItemPositionChanged(const QPointF &pPoint);
    void signal_ItemTransformOriginPointChanged(const QPointF &pPoint);
    void signal_ItemRotationChanged(int newAngle);
    void signal_sendCenterCoords(const QPointF& pPoint);

private slots:
    void addItem();
    void slot_sceneSelectionChanged(QList<QGraphicsItem *> pSelected);
    void applyTransform(const QTransform &pTransform);
    void applyPosition(const QPointF &newPoint);
    void applyTransformOriginPoint(const QPointF &newPoint);
    void applyNewAngle(int newAngle);
    void reactOnCenterCoordsRequest();
    void changeRubberBandDragMode();
    void startTest(const requestContent &req);

private:
    void setupUi();

private:
    MainScene *mScene;
    GraphView *mView;
    QPushButton *mRubberBandDragModeButton;
    QPushButton *mHandDragModeButton;
};

class GraphView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphView(QWidget *parent = 0);
    QSize sizeHint() const;

    friend class CentralView;

};

class MainScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MainScene(QObject *parent = 0);

    void notifyTransformed(const QTransform &pNewTransform, QGraphicsItem *me = 0);
    void notifyMoved(const QPointF &pNewPositon, QGraphicsItem *me = 0);
    void notifyOrginPointChanged(const QPointF &newPoint, QGraphicsItem *me = 0);
    void notifyRotated(int newAngle, QGraphicsItem *me = 0);

signals:
    void selectionChanged(QList<QGraphicsItem*> pSelected);

    void transformChanged(const QTransform &pNewTransform);
    void positionChanged(const QPointF &pNewPositon);
    void transformOriginPointChanged(const QPointF &newPoint);
    void rotationChanged(int newAngle);

private slots:
    void slot_selectionChanged();

private:
    void addCoords();
    void addScale();

};

#endif // CENTRALVIEW_H
