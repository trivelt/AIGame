#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include "vectorhelper.h"

void test()
{
    QVector2D position(5, 20);
    QVector2D pointInGlobalSpace(8, 15);
    QVector2D heading(1,0);
    QVector2D expectedPositionInLocalSpace(3, -5);
    QVector2D computedPositionInLocalSpace = VectorHelper::pointToLocalSpace(pointInGlobalSpace, heading, position);
    if(expectedPositionInLocalSpace != computedPositionInLocalSpace)
    {
        qDebug() << "Expected=" << expectedPositionInLocalSpace << ", computed=" << computedPositionInLocalSpace;
        Q_ASSERT(false);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    test();
    w.show();

    return a.exec();
}
