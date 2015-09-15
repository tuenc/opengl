#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H
#include <glm.hpp>
#include "vertex.h"
class ShapeGenerator
{
public:
    ShapeGenerator();
public:
    static ShapeData makeTriangle();
    static ShapeData makeCube();
};

#endif // SHAPEGENERATOR_H
