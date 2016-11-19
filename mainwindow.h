#ifndef __MAINWINDOW__H__
#define __MAINWINDOW__H__

#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include "graphicsscene.h"
#include "graphicsview.h"

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow();

private:
    GraphicsScene *scene;
    GraphicsView *view;
};

#endif //__MAINWINDOW__H__
