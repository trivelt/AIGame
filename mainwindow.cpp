#include "mainwindow.h"
#include "logger.h"

#include <QGraphicsView>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QLayout>

#ifndef QT_NO_OPENGL
# include <QtOpenGL/QtOpenGL>
#endif

MainWindow::MainWindow() : QMainWindow(0)
{
    Logger::log("Starting game");
    scene = new GraphicsScene(0, 0, 750, 400);
    setWindowState(Qt::WindowFullScreen);

    view = new GraphicsView(scene, this);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene->setupScene();
    view->setBackgroundBrush(QBrush(Qt::red, Qt::SolidPattern));



//#ifndef QT_NO_OPENGL
//    view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
//#endif

    setCentralWidget(view);

}
