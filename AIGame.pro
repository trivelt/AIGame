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
    enemy.cpp \
    laser.cpp \
    steeringbehaviors.cpp \
    vectorhelper.cpp \
    vehicle.cpp \
    circleitem.cpp \
    debugframe.cpp

HEADERS  += mainwindow.h \
    graphicsscene.h \
    pixmapitem.h \
    logger.h \
    graphicsview.h \
    utils.h \
    hero.h \
    enemy.h \
    laser.h \
    steeringbehaviors.h \
    vectorhelper.h \
    vehicle.h \
    circleitem.h \
    debugframe.h


RESOURCES += \
    images.qrc
