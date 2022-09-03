#pragma once

#include <glm/glm.hpp>

class Transform
{
public:
    glm::mat2 rotation;
    glm::vec2 position;

    void translate(const glm::vec2 &v);
    void rotate(float angle);
    void setRotation(float angle);
    void scale(const glm::vec2 &v);
    void lookAt(const glm::vec2 &target);

    float getRotation();

    glm::mat3x2 getMatrix() const { return glm::mat3x2(rotation[0], rotation[1], position); }

    Transform() : rotation(1), position(0) {}
};