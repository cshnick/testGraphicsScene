#-------------------------------------------------
#
# Project created by QtCreator 2013-05-21T15:01:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testScene
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CentralView.cpp \
    ControlDock.cpp \
    GraphicsTestItem.cpp

HEADERS  += mainwindow.h \
    CentralView.h \
    ControlDock.h \
    GraphicsTestItem.h

FORMS    += mainwindow.ui \
    dockWidget.ui
