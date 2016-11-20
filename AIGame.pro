#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T09:17:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AIGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsscene.cpp \
    pixmapitem.cpp \
    logger.cpp \
    graphicsview.cpp \
    utils.cpp \
    hero.cpp \
    enemy.cpp

HEADERS  += mainwindow.h \
    graphicsscene.h \
    pixmapitem.h \
    logger.h \
    graphicsview.h \
    utils.h \
    hero.h \
    enemy.h


RESOURCES += \
    images.qrc
