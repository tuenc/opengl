#include "MyGLWidget.h"
#include <QDebug>
#include <gtc/matrix_transform.hpp>
#include "primitive/shapegenerator.h"
#include "primitive/vertex.h"
#include <gl/GLU.h>
// using namepsace glm ---> error
using glm::vec3;
using glm::vec4;
using glm::mat4;
const GLfloat X_PI = (GLfloat)M_PI;
const GLfloat X_DELTA = 0.1f;
const GLuint NUM_VERTICES_PER_TRI = 3;
const GLuint NUM_FLOAT_PER_VERTICE = 6;
const GLuint TRIANGLE_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOAT_PER_VERTICE * sizeof(GLfloat);
const GLuint MAX_TRIS = 20;
GLuint numTris = 0;
struct Vector {
    GLfloat x,y,z;
};
GLsizei numIndex;
GLuint programID;
GLfloat gRotate = 54.0 * X_PI / 180;
MyGLWidget::MyGLWidget(QWidget *parent) : QGLWidget(parent), QOpenGLFunctions()
{
    m_zoomLvl = 1.0f;
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
}
// callback function
void CALLBACK tessBeginCB(GLenum which)
{
    glBegin(which);
    qDebug() << "glBegin(" << which << ")";
}

void CALLBACK tessEndCB()
{
    glEnd();
    qDebug() << "glEnd()";
}

void CALLBACK tessVertexCB(const GLvoid *data)
{
    const GLdouble *ptr = (const GLdouble*) data;
    glVertex3dv(ptr);
    qDebug() << "glVertex3dv(" << *ptr << ", " << *(ptr+1) << ", " << *(ptr+2) << ")";
}
void CALLBACK tessErrorCB(GLenum errorCode)
{
    const GLubyte *errorStr;
    errorStr = gluErrorString(errorCode);
    qDebug() << "[error]:" << errorStr;
}

// end callback function
void MyGLWidget::resizeGL(int w, int h)
{

    glViewport(0, 0, w*2, h);
}

GLuint listTessellateID;
#if(0)
void MyGLWidget::paintGL()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    static bool needLoadPolygon = true;
    if(needLoadPolygon){
        needLoadPolygon = false;
        listTessellateID = glGenLists(1);
        GLUtesselator *tess = gluNewTess();
        GLdouble quad2[12][3] = {
            {-0.5, +0.5, +0.0}, {+0.5, +0.5, +0.0}, {+0.5, -0.5, +0.0}, {-0.5, -0.5, +0.0} ,
            {-0.4, +0.1, +0.0}, {-0.2, +0.1, +0.0}, {-0.2, -0.1, +0.0}, {-0.4, -0.1, +0.0} ,
            {+0.2, +0.1, +0.0}, {+0.4, +0.1, +0.0}, {+0.4, -0.1, +0.0}, {+0.2, -0.1, +0.0} ,
        };

        // register callback functions
        gluTessCallback(tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCB);
        gluTessCallback(tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCB);
        gluTessCallback(tess, GLU_TESS_ERROR, (void (__stdcall*)(void)) tessErrorCB);
        gluTessCallback(tess, GLU_TESS_VERTEX, (void (__stdcall*)(void)) tessVertexCB);

        // tessellate and compile quad into display list
        glNewList(listTessellateID, GL_COMPILE);
        glColor3f(1,1,1);
        gluTessBeginPolygon(tess,0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad2[0], quad2[0]);
            gluTessVertex(tess, quad2[1], quad2[1]);
            gluTessVertex(tess, quad2[2], quad2[2]);
            gluTessVertex(tess, quad2[3], quad2[3]);
        gluTessEndContour(tess);

        gluTessBeginContour(tess);
            gluTessVertex(tess, quad2[4], quad2[4]);
            gluTessVertex(tess, quad2[5], quad2[5]);
            gluTessVertex(tess, quad2[6], quad2[6]);
            gluTessVertex(tess, quad2[7], quad2[7]);
        gluTessEndContour(tess);

        gluTessBeginContour(tess);
            gluTessVertex(tess, quad2[8], quad2[8]);
            gluTessVertex(tess, quad2[9], quad2[9]);
            gluTessVertex(tess, quad2[10], quad2[10]);
            gluTessVertex(tess, quad2[11], quad2[11]);
        gluTessEndContour(tess);
        gluTessEndPolygon(tess);
        glEndList();
        gluDeleteTess(tess);
    }// end need load


    glViewport(0, 0, width(), height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // zoom mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(m_zoomLvl, 1.0f, 1.0f);

    // draw list
    glCallList(listTessellateID);
}
#endif
GLdouble dataDouble[44][3] = {
    { 0.0332443 ,  -0.388576 , 0.0}
    ,{ 0.0349398 ,  -0.386432 , 0.0}
    ,{ 0.0383341 ,  -0.385946 , 0.0}
    ,{ 0.108415 ,  -0.383896 , 0.0}
    ,{ 0.107118 ,  -0.382681 , 0.0}
    ,{ 0.108215 ,  -0.382103 , 0.0}
    ,{ 0.109414 ,  -0.383397 , 0.0}
    ,{ 0.110513 ,  -0.382752 , 0.0}
    ,{ 0.110213 ,  -0.383327 , 0.0}
    ,{ 0.110413 ,  -0.383754 , 0.0}
    ,{ 0.108415 ,  -0.383896 , 0.0}
    ,{ 0.0839568 ,  -0.384535 , 0.0}
    ,{ 0.0862542 ,  -0.382968 , 0.0}
    ,{ 0.0872511 ,  -0.383682 , 0.0}
    ,{ 0.108815 ,  -0.387337 , 0.0}
    ,{ 0.110012 ,  -0.386574 , 0.0}
    ,{ 0.109614 ,  -0.385946 , 0.0}
    ,{ 0.110413 ,  -0.384821 , 0.0}
    ,{ 0.108815 ,  -0.384677 , 0.0}
    ,{ 0.108215 ,  -0.384466 , 0.0}
    ,{ 0.109414 ,  -0.383969 , 0.0}
    ,{ 0.108815 ,  -0.384677 , 0.0}
    ,{ 0.105621 ,  -0.259333 , 0.0}
    ,{ 0.105321 ,  -0.259606 , 0.0}
    ,{ 0.105121 ,  -0.259199 , 0.0}
    ,{ 0.105321 ,  -0.258512 , 0.0}
    ,{ 0.10572 ,  -0.258925 , 0.0}
    ,{ 0.105621 ,  -0.259333 , 0.0}
    ,{ 0.104723 ,  -0.260157 , 0.0}
    ,{ 0.105121 ,  -0.260973 , 0.0}
    ,{ 0.104423 ,  -0.260701 , 0.0}
    ,{ 0.104723 ,  -0.260157 , 0.0}
    ,{ 0.105321 ,  -0.258925 , 0.0}
    ,{ 0.105521 ,  -0.259059 , 0.0}
    ,{ 0.105321 ,  -0.259333 , 0.0}
    ,{ 0.105321 ,  -0.258925 , 0.0}
    ,{ 0.00948433 ,  -0.302217 , 0.0}
    ,{ 0.0093843 ,  -0.302566 , 0.0}
    ,{ 0.00928427 ,  -0.302335 , 0.0}
    ,{ 0.00948433 ,  -0.302217 , 0.0}
    ,{ 0.110613 ,  -0.379769 , 0.0}
    ,{ 0.110513 ,  -0.379622 , 0.0}
    ,{ 0.110711 ,  -0.379622 , 0.0}
    ,{ 0.110613 ,  -0.379769 , 0.0}
};

void MyGLWidget::paintGL()
{
    glViewport(0, 0, width(), height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // zoom mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(m_zoomLvl, m_zoomLvl, 1.0f);
#if(0)
    glBegin(GL_LINE_LOOP);//GL_LINE_STRIP
    for(int i = 0; i < 44; i++){
        glVertex2d(dataDouble[i][0], dataDouble[i][1]);
    }// end for
    glEnd();
#endif
#if(1)
    static bool needLoadPolygon = true;
    if(needLoadPolygon){
        needLoadPolygon = false;
        listTessellateID = glGenLists(1);
        GLUtesselator *tess = gluNewTess();
        GLdouble quad2[][3] = {
            { 0.0332443 ,  -0.388576 , 0.0}
            ,{ 0.0349398 ,  -0.386432 , 0.0}
            ,{ 0.0383341 ,  -0.385946 , 0.0}
            ,{ 0.108415 ,  -0.383896 , 0.0}
            ,{ 0.107118 ,  -0.382681 , 0.0}
            ,{ 0.108215 ,  -0.382103 , 0.0}
            ,{ 0.109414 ,  -0.383397 , 0.0}
            ,{ 0.110513 ,  -0.382752 , 0.0}
            ,{ 0.110213 ,  -0.383327 , 0.0}
            ,{ 0.110413 ,  -0.383754 , 0.0}
            ,{ 0.108415 ,  -0.383896 , 0.0}
            ,{ 0.0839568 ,  -0.384535 , 0.0}
            ,{ 0.0862542 ,  -0.382968 , 0.0}
            ,{ 0.0872511 ,  -0.383682 , 0.0}
            ,{ 0.108815 ,  -0.387337 , 0.0}
            ,{ 0.110012 ,  -0.386574 , 0.0}
            ,{ 0.109614 ,  -0.385946 , 0.0}
            ,{ 0.110413 ,  -0.384821 , 0.0}
            ,{ 0.108815 ,  -0.384677 , 0.0}
            ,{ 0.108215 ,  -0.384466 , 0.0}
            ,{ 0.109414 ,  -0.383969 , 0.0}
            ,{ 0.108815 ,  -0.384677 , 0.0}
            ,{ 0.105621 ,  -0.259333 , 0.0}
            ,{ 0.105321 ,  -0.259606 , 0.0}
            ,{ 0.105121 ,  -0.259199 , 0.0}
            ,{ 0.105321 ,  -0.258512 , 0.0}
            ,{ 0.10572 ,  -0.258925 , 0.0}
            ,{ 0.105621 ,  -0.259333 , 0.0}
            ,{ 0.104723 ,  -0.260157 , 0.0}
            ,{ 0.105121 ,  -0.260973 , 0.0}
            ,{ 0.104423 ,  -0.260701 , 0.0}
            ,{ 0.104723 ,  -0.260157 , 0.0}
            ,{ 0.105321 ,  -0.258925 , 0.0}
            ,{ 0.105521 ,  -0.259059 , 0.0}
            ,{ 0.105321 ,  -0.259333 , 0.0}
            ,{ 0.105321 ,  -0.258925 , 0.0}
            ,{ 0.00948433 ,  -0.302217 , 0.0}
            ,{ 0.0093843 ,  -0.302566 , 0.0}
            ,{ 0.00928427 ,  -0.302335 , 0.0}
            ,{ 0.00948433 ,  -0.302217 , 0.0}
            ,{ 0.110613 ,  -0.379769 , 0.0}
            ,{ 0.110513 ,  -0.379622 , 0.0}
            ,{ 0.110711 ,  -0.379622 , 0.0}
            ,{ 0.110613 ,  -0.379769 , 0.0}
        };

        // register callback functions
        gluTessCallback(tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCB);
        gluTessCallback(tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCB);
        gluTessCallback(tess, GLU_TESS_ERROR, (void (__stdcall*)(void)) tessErrorCB);
        gluTessCallback(tess, GLU_TESS_VERTEX, (void (__stdcall*)(void)) tessVertexCB);

        // tessellate and compile quad into display list
        glNewList(listTessellateID, GL_COMPILE);
        glColor3f(1,1,1);
        gluTessBeginPolygon(tess,0);
            gluTessBeginContour(tess);
                for(int i = 0; i < sizeof(quad2)/(3*sizeof(GLdouble)); i++){
                    gluTessVertex(tess, quad2[i], quad2[i]);
                }// end for
            gluTessEndContour(tess);
        gluTessEndPolygon(tess);
        glEndList();
        gluDeleteTess(tess);
    }// end need load
    // draw list
    glCallList(listTessellateID);
#endif
}// end function

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
        m_zoomLvl *= 1.2f;
    }else{
        m_zoomLvl /= 1.2f;
    }
    /*glViewport(0,0,width()*roomLvl, height() * roomLvl);*/
    repaint();
    qDebug() << m_zoomLvl;
}
