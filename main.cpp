#include "mainwindow.h"
#include <QApplication>
#include <QtCore>
#include <QtGui>

struct a
{
    virtual void foo()
    {
        qDebug() << "a.func";
    }
};

struct b : public virtual a
{
    void foo()
    {
        qDebug() << "b.func";
    }
};

struct c : public b, public virtual a
{
    virtual void foo()
    {
        qDebug() << "c.func";
//        a::foo();
        b::foo();
    }
};

int main(int argc, char *argv[])
{
    a a1;
    a1.foo();

    b b1;
    b1.foo();

    c c1;
    c1.foo();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
