#include "MyGLWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyGLWidget mgl;
    mgl.show();

    return a.exec();
}
