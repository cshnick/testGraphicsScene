#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CentralView.h"
#include "ControlDock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , mCentralWidget(0)
  , mControlDock(0)
{
    ui->setupUi(this);
    mCentralWidget = new CentralView(this);
    mControlDock = new ControlDock(this);
    setCentralWidget(mCentralWidget);
    addDockWidget(Qt::LeftDockWidgetArea, mControlDock);

    setGeometry(0, 0, mCentralWidget->sizeHint().width() + 400, mCentralWidget->sizeHint().height() + 100);

    connect(mCentralWidget, SIGNAL(signal_ItemTransformChanged(QTransform)), mControlDock, SLOT(writeTransform(QTransform)));
    connect(mCentralWidget, SIGNAL(signal_ItemTransformOriginPointChanged(QPointF)), mControlDock, SLOT(writeTransformOriginPoint(QPointF)));
    connect(mCentralWidget, SIGNAL(signal_ItemPositionChanged(QPointF)), mControlDock, SLOT(writePosition(QPointF)));
    connect(mCentralWidget, SIGNAL(signal_ItemRotationChanged(int)), mControlDock, SLOT(writeRotation(int)));

    connect(mControlDock, SIGNAL(requestAddItem()), mCentralWidget, SLOT(addItem()));
    connect(mControlDock, SIGNAL(requestSetNewTransform(QTransform)), mCentralWidget, SLOT(applyTransform(QTransform)));
    connect(mControlDock, SIGNAL(requestSetNewPosition(QPointF)), mCentralWidget, SLOT(applyPosition(QPointF)));
    connect(mControlDock, SIGNAL(requestSetNewTransformOriginPoint(QPointF)), mCentralWidget, SLOT(applyTransformOriginPoint(QPointF)));
    connect(mControlDock, SIGNAL(requestSetNewRotationAngle(int)), mCentralWidget, SLOT(applyNewAngle(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
