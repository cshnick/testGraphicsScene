#ifndef TESTDOCK_H
#define TESTDOCK_H

#include <QDockWidget>

#include <QtGui>

class TestDockWidget;
namespace Ui {
class TestDockWidget;
}

class TestDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit TestDock(QWidget *parent = 0);

private:
    TestDockWidget *mWidget;

    friend class TestDockWidget;
};

class TestDockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestDockWidget(QWidget *parent = 0);
    ~TestDockWidget();


    Ui::TestDockWidget *ui;
    TestDock *q;

    friend class TestDock;
};

#endif // TESTDOCK_H
