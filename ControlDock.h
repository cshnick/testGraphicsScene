#ifndef CONTROLDOCK_H
#define CONTROLDOCK_H

#include <QDockWidget>

#include <QtGui>

class ControlDockWidget;
namespace Ui {
class DockWidget;
}


class ControlDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit ControlDock(QWidget *parent = 0);
    
signals:
    void requestAddItem();
    void angleChanged(int pValue);
    void requestSetNewTransform(const QTransform &pTransform);
    void requestSetNewPosition(const QPointF &newPos);
    void requestSetNewTransformOriginPoint(const QPointF &newPos);
    void requestSetNewRotationAngle(int newAngle);
    
private slots:
    void writeTransform(const QTransform &pTransform);
    void writePosition(const QPointF &pPoint);
    void writeRotation(int pNewAngle);
    void writeTransformOriginPoint(const QPointF &pPoint);

private:
    ControlDockWidget *mWidget;

    friend class ControlDockWidget;
};

class ControlDockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlDockWidget(QWidget *parent = 0);
    ~ControlDockWidget();

private:
    void writeTransform(const QTransform &pTransform);

    Ui::DockWidget *ui;
    ControlDock *q;

    friend class ControlDock;

private slots:
        void requestSetNewTransform();
        void requestSetNewPosition();
        void requestSetNewTransformOriginPoint();
};

#endif // CONTROLDOCK_H
