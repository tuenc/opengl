#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui/QOpenGLFunctions>

using namespace std;

class MyGLWidget : public QGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
    QTimer *m_timer;
public slots:
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void wheelEvent(QWheelEvent *event);
protected:
    float m_zoomLvl;
};

#endif // MYGLWIDGET_H
