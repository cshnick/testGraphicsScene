#include "TestDock.h"

#include "ui_TestDock.h"

#include <QtGui>

TestDock::TestDock(QWidget *parent) :
    QDockWidget(parent)

{
    mWidget = new TestDockWidget(this);
    setWidget(mWidget);

    connect(mWidget->ui->startTestButton, SIGNAL(clicked()), this, SLOT(generateRequest()));

//    connect(mWidget->ui->dial, SIGNAL(valueChanged(int)), this, SIGNAL(angleChanged(int)));
//    connect(mWidget->ui->toolButton, SIGNAL(clicked()), this, SIGNAL(requestAddItem()));
//    connect(mWidget->ui->dial, SIGNAL(valueChanged(int)), this, SIGNAL(requestSetNewRotationAngle(int)));

//    connect(mWidget->ui->applyTransformButton, SIGNAL(clicked()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m11, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m12, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m13, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m21, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m22, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m23, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m31, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m32, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));
//    connect(mWidget->ui->m33, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransform()));

//    connect(mWidget->ui->setNewPosButton, SIGNAL(clicked()), mWidget, SLOT(requestSetNewPosition()));
//    connect(mWidget->ui->pos_x, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewPosition()));
//    connect(mWidget->ui->pos_y, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewPosition()));

//    connect(mWidget->ui->setNewTopButton, SIGNAL(clicked()), mWidget, SLOT(requestSetNewTransformOriginPoint()));
//    connect(mWidget->ui->top_x, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransformOriginPoint()));
//    connect(mWidget->ui->top_y, SIGNAL(editingFinished()), mWidget, SLOT(requestSetNewTransformOriginPoint()));
//    connect(mWidget->ui->topCenterButton, SIGNAL(clicked()), mWidget, SLOT(requestCenterCoords()));
}

void TestDock::generateRequest()
{
    requestContent req;
    req.itemType = mWidget->ui->itemTypeCombobox->currentText();
    req.numItems = mWidget->ui->numberIemsButton->value();

    emit sendTestRequest(req);
}

TestDockWidget::TestDockWidget(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::TestDockWidget)
    , q(static_cast<TestDock*>(parent))
{
    ui->setupUi(this);

    ui->numberIemsButton->setValue(NUMITEMS);
    ui->itemTypeCombobox->addItem(PATH_ITEM);
    ui->itemTypeCombobox->addItem(PIX_ITEM);

}

TestDockWidget::~TestDockWidget()
{
    delete ui;
}
