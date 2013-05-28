#ifndef PropertiesDock_H
#define PropertiesDock_H

#include <QDockWidget>

#include <QtGui>

class PropertiesDockWidget;
namespace Ui {
class DockWidget;
}


class PropertiesDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit PropertiesDock(QWidget *parent = 0);
    
signals:
    void requestAddItem();
    void angleChanged(int pValue);
    void requestSetNewTransform(const QTransform &pTransform);
    void requestSetNewPosition(const QPointF &newPos);
    void requestSetNewTransformOriginPoint(const QPointF &newPos);
    void requestSetNewRotationAngle(int newAngle);
    void requestCenterCoords();
    
private slots:
    void writeTransform(const QTransform &pTransform);
    void writePosition(const QPointF &pPoint);
    void writeRotation(int pNewAngle);
    void writeTransformOriginPoint(const QPointF &pPoint);

private:
    PropertiesDockWidget *mWidget;

    friend class PropertiesDockWidget;
};

class PropertiesDockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesDockWidget(QWidget *parent = 0);
    ~PropertiesDockWidget();

private:
    void writeTransform(const QTransform &pTransform);

    Ui::DockWidget *ui;
    PropertiesDock *q;

    friend class PropertiesDock;

private slots:
        void requestSetNewTransform();
        void requestSetNewPosition();
        void requestSetNewTransformOriginPoint();
        void requestCenterCoords();
};

#endif // PropertiesDock_H
