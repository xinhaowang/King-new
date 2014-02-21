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
    eventmagic.cpp \
    hero.cpp \
    control.cpp \
    combat.cpp \
    mylabel.cpp

HEADERS  += mainwindow.h \
    player.h \
    thing.h \
    building.h \
    hex.h \
    eventmagic.h \
    hero.h \
    control.h \
    combat.h \
    mylabel.h

FORMS    += mainwindow.ui \
    combat.ui

RESOURCES += \
    Image.qrc
