#pragma once

#include "application.h"

class SpaceBody
{
public:
    static const int name_size = 15;
    char name[name_size];
    Mesh2D<ColoredVertex2D> mesh;
    Transform transform;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float mass;

    void create(const char* lable, const glm::vec3 &color, float _radius, int quality)
    {
        mesh = Mesh2D<ColoredVertex2D>::createCircle(1.0f, quality, color);
        radius = _radius;
        setRadius(radius);
        strcpy(name, lable);
    };
    void draw() const { mesh.draw(); }

    void destroy() const { mesh.destroy(); }

    SpaceBody() {}
    SpaceBody(const char* lable, const glm::vec3 &color, float radius, int quality = 15)
    {
        create(lable, color, radius, quality);
    }

    void setRadius(float r)
    {
        radius = r;
        transform.rotation[0].x = transform.rotation[1].y = r;
    }

    float getRadius() const { return radius; }

private:
    float radius;
};