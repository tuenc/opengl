#pragma once
#include <QtOpenGL>
struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

struct ShapeData
{
    ShapeData() :
        vertices(0), numVertices(0),
        indices(0), numIndices(0)
    {}
    //~ShapeData()
    void cleanup()
    {
        if(vertices)
            delete [] vertices;
        if(indices)
            delete [] indices;

        numVertices = 0;
        numIndices = 0;
    }

    Vertex* vertices;
    GLuint numVertices;
    GLushort* indices;
    GLuint numIndices;

    GLsizeiptr vertexBufferSize() const
    {
        return numVertices * sizeof(Vertex);
    }

    GLsizeiptr indexBufferSize() const
    {
        return numIndices * sizeof(GLushort);
    }
};
