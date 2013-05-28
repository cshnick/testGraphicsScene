#include "PropertiesDock.h"
#include "ui_PropertiesDockWidget.h"

#include <QtGui>

PropertiesDock::PropertiesDock(QWidget *parent) :
    QDockWidget(parent)

{
    mWidget = new PropertiesDockWidget(this);
    setWidget(mWidget);

    connect(mWidget->ui->dial, SIGNAL(valueChanged(int)), this, SIGNAL(angleChanged(int)));
    connect(mWidget->ui->toolButton, SIGNAL(clicked()), this, SIGNAL(requestAddItem()));
    connect(mWidget->ui->dial, SIGNAL(valueChanged(int)), this, SIGNAL(requestSetNewRotationAngle(int)));

    connect(mWidget->ui->applyTransformButton, SIGNAL(clicked()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m11, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m12, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m13, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m21, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m22, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m23, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m31, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m32, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
    connect(mWidget->ui->m33, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));

    connect(mWidget->ui->setNewPosButton, SIGNAL(clicked()), mWidget, SLOT(requestSetNewPosition()));
    connect(mWidget->ui->pos_x, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewPosition()));
    connect(mWidget->ui->pos_y, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewPosition()));

    connect(mWidget->ui->setNewTopButton, SIGNAL(clicked()), mWidget, SLOT(requestSetNewTransformOriginPoint()));
    connect(mWidget->ui->top_x, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransformOriginPoint()));
    connect(mWidget->ui->top_y, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransformOriginPoint()));
    connect(mWidget->ui->topCenterButton, SIGNAL(clicked()), mWidget, SLOT(requestCenterCoords()));
}

void PropertiesDock::writeTransform(const QTransform &pTransform)
{
    mWidget->writeTransform(pTransform);
}

void PropertiesDock::writePosition(const QPointF &pPoint)
{
    mWidget->ui->pos_x->setValue(pPoint.x());
    mWidget->ui->pos_y->setValue(pPoint.y());
}

void PropertiesDock::writeRotation(int pNewAngle)
{
    mWidget->ui->dial->setValue(pNewAngle);
}

void PropertiesDock::writeTransformOriginPoint(const QPointF &pPoint)
{
    mWidget->ui->top_x->setValue(pPoint.x());
    mWidget->ui->top_y->setValue(pPoint.y());
}

PropertiesDockWidget::PropertiesDockWidget(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::DockWidget)
    , q(static_cast<PropertiesDock*>(parent))
{
    ui->setupUi(this);

    ui->dial->setMinimum(0);
    ui->dial->setMaximum(360);
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(360);

    connect(ui->dial, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->dial, SLOT(setValue(int)));
    ui->dial->setValue(0);
}

PropertiesDockWidget::~PropertiesDockWidget()
{
    delete ui;
}

void PropertiesDockWidget::writeTransform(const QTransform &pTransform)
{
    qreal m11 = pTransform.m11();
    qreal m22 = pTransform.m22();
    qreal m12 = pTransform.m12();
    qreal m21 = pTransform.m21();
    qreal m13 = pTransform.m13();
    qreal m23 = pTransform.m23();
    qreal m31 = pTransform.m31();
    qreal m32 = pTransform.m32();
    qreal m33 = pTransform.m33();

    ui->m11->setValue(m11);
    ui->m22->setValue(m22);
    ui->m12->setValue(m12);
    ui->m21->setValue(m21);
    ui->m13->setValue(m13);
    ui->m23->setValue(m23);
    ui->m31->setValue(m31);
    ui->m32->setValue(m32);
    ui->m33->setValue(m33);
}


void PropertiesDockWidget::requestSetNewTransform()
{
    QTransform transform (
                ui->m11->value()
                , ui->m12->value()
                , ui->m13->value()
                , ui->m21->value()
                , ui->m22->value()
                , ui->m23->value()
                , ui->m31->value()
                , ui->m32->value()
                , ui->m33->value()
                );

    emit q->requestSetNewTransform(transform);
}

void PropertiesDockWidget::requestSetNewPosition()
{
    QPointF newPoint(ui->pos_x->value(), ui->pos_y->value());
    emit q->requestSetNewPosition(newPoint);
}

void PropertiesDockWidget::requestSetNewTransformOriginPoint()
{
    QPointF newPoint(ui->top_x->value(), ui->top_y->value());
    emit q->requestSetNewTransformOriginPoint(newPoint);
}

void PropertiesDockWidget::requestCenterCoords()
{
    emit q->requestCenterCoords();
}
