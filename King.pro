#-------------------------------------------------
#
# Project created by QtCreator 2014-02-20T10:26:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = King
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    thing.cpp \
    building.cpp \
    hex.cpp \
    hero.cpp \
    control.cpp \
    combat.cpp \
    mylabel.cpp \
    mapwidget.cpp \
    hexwidget.cpp \
    herolabel.cpp \
    dicewidget.cpp

HEADERS  += mainwindow.h \
    player.h \
    thing.h \
    building.h \
    hex.h \
    hero.h \
    control.h \
    combat.h \
    mylabel.h \
    mapwidget.h \
    hexwidget.h \
    ThingMimeData.h \
    herolabel.h \
    dicewidget.h

FORMS    += mainwindow.ui \
    combat.ui

RESOURCES += \
    Image.qrc

CONFIG += console
