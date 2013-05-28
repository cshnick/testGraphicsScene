#ifndef TESTDOCK_H
#define TESTDOCK_H

#include <QDockWidget>

#include <QtGui>

#define NUMITEMS 4000
#define PATH_ITEM "GraphicsPathTstItem"
#define PIX_ITEM "GraphicsPixmapTstItem"

class TestDockWidget;
namespace Ui {
class TestDockWidget;
}

struct requestContent
{
    requestContent()
        : numItems(NUMITEMS)
    {
    }

    QString itemType;
    int numItems;
};

class TestDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit TestDock(QWidget *parent = 0);

signals:
    void sendTestRequest(const requestContent &content);

private slots:
    void generateRequest();

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
