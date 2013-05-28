#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CentralView.h"
#include "PropertiesDock.h"
#include "TestDock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , mCentralWidget(0)
  , mPropertiesDock(0)
  , mTestDock(0)
{
    ui->setupUi(this);
    mCentralWidget = new CentralView(this);
    mPropertiesDock = new PropertiesDock(this);
    mTestDock = new TestDock(this);

    setCentralWidget(mCentralWidget);
    addDockWidget(Qt::LeftDockWidgetArea, mPropertiesDock);
    addDockWidget(Qt::TopDockWidgetArea, mTestDock);

    setGeometry(0, 0, mCentralWidget->sizeHint().width() + 400, mCentralWidget->sizeHint().height() + 100);

    connect(mCentralWidget, SIGNAL(signal_ItemTransformChanged(QTransform)), mPropertiesDock, SLOT(writeTransform(QTransform)));
    connect(mCentralWidget, SIGNAL(signal_ItemTransformOriginPointChanged(QPointF)), mPropertiesDock, SLOT(writeTransformOriginPoint(QPointF)));
    connect(mCentralWidget, SIGNAL(signal_ItemPositionChanged(QPointF)), mPropertiesDock, SLOT(writePosition(QPointF)));
    connect(mCentralWidget, SIGNAL(signal_ItemRotationChanged(int)), mPropertiesDock, SLOT(writeRotation(int)));
    connect(mCentralWidget, SIGNAL(signal_sendCenterCoords(QPointF)), mPropertiesDock, SLOT(writeTransformOriginPoint(QPointF)));

    connect(mPropertiesDock, SIGNAL(requestAddItem()), mCentralWidget, SLOT(addItem()));
    connect(mPropertiesDock, SIGNAL(requestSetNewTransform(QTransform)), mCentralWidget, SLOT(applyTransform(QTransform)));
    connect(mPropertiesDock, SIGNAL(requestSetNewPosition(QPointF)), mCentralWidget, SLOT(applyPosition(QPointF)));
    connect(mPropertiesDock, SIGNAL(requestSetNewTransformOriginPoint(QPointF)), mCentralWidget, SLOT(applyTransformOriginPoint(QPointF)));
    connect(mPropertiesDock, SIGNAL(requestSetNewRotationAngle(int)), mCentralWidget, SLOT(applyNewAngle(int)));
    connect(mPropertiesDock, SIGNAL(requestCenterCoords()), mCentralWidget, SLOT(reactOnCenterCoordsRequest()));

    connect(mTestDock, SIGNAL(sendTestRequest(requestContent)), mCentralWidget, SLOT(startTest(requestContent)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
