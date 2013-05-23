#ifndef CENTRALVIEW_H
#define CENTRALVIEW_H

#include <QGraphicsView>
#include <QtGui>

class MainScene;
class GraphicsTestItem;

class CentralView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CentralView(QWidget *parent = 0);

    QSize sizeHint() const;

signals:
    void signal_ItemTransformChanged(const QTransform &pTransform);
    void signal_ItemPositionChanged(const QPointF &pPoint);
    void signal_ItemTransformOriginPointChanged(const QPointF &pPoint);
    void signal_ItemRotationChanged(int newAngle);
    void signal_sendCenterCoords(const QPointF& pPoint);

private slots:
    void addItem();
    void slot_sceneSelectionChanged(QList<GraphicsTestItem*> pSelected);
    void applyTransform(const QTransform &pTransform);
    void applyPosition(const QPointF &newPoint);
    void applyTransformOriginPoint(const QPointF &newPoint);
    void applyNewAngle(int newAngle);
    void reactOnCenterCoordsRequest();
        
private:
    MainScene *mScene;
    
};

class MainScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MainScene(QObject *parent = 0);

signals:
    void selectionChanged(QList<GraphicsTestItem*> pSelected);

private slots:
    void slot_selectionChanged();

private:
    void addCoords();
    void addScale();

};

#endif // CENTRALVIEW_H
