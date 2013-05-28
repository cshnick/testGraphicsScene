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
    GraphicsTestItem.cpp \
    PropertiesDock.cpp \
    TestDock.cpp

HEADERS  += mainwindow.h \
    CentralView.h \
    GraphicsTestItem.h \
    PropertiesDock.h \
    TestDock.h

FORMS    += mainwindow.ui \
    PropertiesDockWidget.ui \
    TestDock.ui
