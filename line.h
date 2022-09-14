#pragma once

#include "shader.h"
#include "mesh2D.h"
#include "transform.h"

class Line
{
    const Shader *shader;
    Mesh2D<ColoredVertex2D> line;

public:
    Transform transform;

    Line() : shader(&Shader::color_shader) {}

    ~Line()
    {
        line.destroy();
    }

    void create()
    {
        line = Mesh2D<ColoredVertex2D>::createLine();
    }

    void setPoints(const glm::vec2 &p1, const glm::vec2 &p2)
    {
        transform.position = p1;
        glm::vec2 v = p2 - p1;
        transform.rotation[0].x = v.x;
        transform.rotation[1].y = v.y;
    }

    void draw()
    {
        shader->setMat3x2("m", transform.getMatrix());
        line.draw();
    }
};