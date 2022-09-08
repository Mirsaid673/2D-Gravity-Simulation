#pragma once

#include "space_body.h"

class Space
{
private:
    std::vector<SpaceBody> bodies;

public:
    const Shader *shader;

    glm::vec3 color = glm::vec3(0.0f);
    glm::vec2 pos = glm::vec2(0.0f);
    glm::vec2 velocity = glm::vec2(0.0f);
    float mass = 1.0f;
    float radius = 0.5f;
    int quality = 15;

    float gravity_const = 1.0f;

    void add()
    {
        bodies.push_back(SpaceBody(color, radius, quality));
        SpaceBody &last = bodies.back();
        last.transform.position = pos;
        last.velocity = velocity;
        last.acceleration = glm::vec2(0.0f);
        last.mass = mass;
    }

    void update_physics(float delta)
    {
        // update all accelerations
        for (int i = 0; i < bodies.size(); i++)
        {
            for (int j = i + 1; j < bodies.size(); j++)
            {
                glm::vec2 direction = bodies[j].transform.position - bodies[i].transform.position;
                float distance = glm::length(direction);
                direction /= distance; // normalizing direction
                float G_distance_square = gravity_const / (distance * distance);

                bodies[i].acceleration += (bodies[j].mass * G_distance_square) * direction;
                bodies[j].acceleration += -(bodies[i].mass * G_distance_square) * direction;
            }
        }

        for (auto &body : bodies)
        {
            glm::vec2 new_velocity = body.velocity + body.acceleration * delta;
            body.transform.position += (body.velocity + new_velocity) * delta / 2.0f;
            body.velocity = new_velocity;
            body.acceleration = glm::vec2(0);
        }
    }

    void draw()
    {
        for (const auto &body : bodies)
        {
            shader->setMat3x2("m", body.transform.getMatrix());
            body.draw();
        }
    }

    Space() : shader(&Shader::color_shader) {}
};