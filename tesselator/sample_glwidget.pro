#-------------------------------------------------
#
# Project created by QtCreator 2015-06-12T13:51:02
#
#-------------------------------------------------
QT += widgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sample_glwidget
TEMPLATE = app


SOURCES += main.cpp \
    MyGLWidget.cpp \
    primitive/shapegenerator.cpp

HEADERS  += \
    MyGLWidget.h \
    primitive/vertex.h \
    primitive/shapegenerator.h

OTHER_FILES += \
    VertexShaderCode.vert \
    FragmentShaderCode.frag
INCLUDEPATH += library\glm\glm

RESOURCES += \
    ShaderCode.qrc
