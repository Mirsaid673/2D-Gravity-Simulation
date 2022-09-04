#pragma once

#include "application.h"

class SpaceBody
{
public:
    Transform transform;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float mass;

    void create(const glm::vec3 &color, float radius, int quality = 15) { mesh = Mesh2D<ColoredVertex2D>::createCircle(radius, quality, color); };
    void draw() const { mesh.draw(); }

    void destroy() const { mesh.destroy(); }

    SpaceBody() {}
    SpaceBody(const glm::vec3 &color, float radius, int quality = 15) { create(color, radius, quality); }

private:
    Mesh2D<ColoredVertex2D> mesh;
};