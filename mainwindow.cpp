#include "mainwindow.h"

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
    scene = new GraphicsScene(0, 0, 750, 400);
    setWindowState(Qt::WindowFullScreen);

    view = new QGraphicsView(scene, this);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene->setupScene();


//#ifndef QT_NO_OPENGL
//    view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
//#endif

    setCentralWidget(view);

}
