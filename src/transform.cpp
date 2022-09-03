#include "transform.h"

void Transform::translate(const glm::vec2 &v)
{
    position += glm::vec2(glm::dot(glm::vec2(rotation[0].x, rotation[1].x), v), glm::dot(glm::vec2(rotation[0].y, rotation[1].y), v));
}

void Transform::rotate(float angle)
{
    glm::mat2 r;
    float s = std::sin(angle);
    float c = std::cos(angle);
    r = glm::mat2(c, -s, s, c);

    rotation = r * rotation;
}

void Transform::setRotation(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);
    rotation = glm::mat2(c, -s, s, c);
}

void Transform::scale(const glm::vec2 &v)
{
    rotation[0] *= v.x;
    rotation[1] *= v.y;
}
