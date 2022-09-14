#pragma once

#include "application.h"
#include "space.h"
#include "line.h"

class MyGame : public Application
{
    Space space;
    SpaceBody *current = nullptr;
    glm::vec2 current_vel = glm::vec2(0);
    bool to_add = false;
    bool pause = false;
    bool is_pressed_in_viewport = false;
    glm::ivec2 start_pos = glm::vec2(-1);
    Line line;

    void init() override
    {
        camera.scale = (float)viewport_size.x / 50;
        clear_color = glm::vec3(0.2f, 0.3f, 0.6f);
        line.create();
        line.setPoints(glm::vec2(0), glm::vec2(0));
    }
    void update() override
    {
        if (to_add)
        {
            space.add();
            to_add = false;
        }

        if (!pause)
            space.update_physics(1.0 / 60.0);

        if (isInside(viewport_pos, viewport_size, Input::getCursorPos()))
        {
            glm::ivec2 c_p = Input::getCursorPos() - viewport_pos;
            glm::vec2 world_pos = getCursorWorldPosition(c_p) + camera.transform.position;

            if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
                camera.transform.position -= getCursorWorldOffset(Input::getCursorOffset());

            else if (Input::getMouseButtonPress(GLFW_MOUSE_BUTTON_LEFT))
            {
                is_pressed_in_viewport = true;

                current = nullptr;
                for (auto &obj : space.bodies)
                {
                    if (isPointInsideCircle(world_pos, obj.transform.position, obj.getRadius()))
                        current = &obj;
                }

                if (current)
                {
                    current_vel = current->velocity;
                    current->velocity = glm::vec2(0);
                }
                else
                {
                    space.pos = world_pos;
                    start_pos = Input::getCursorPos() - viewport_pos;

                    glm::vec2 start_world = getCursorWorldPosition(start_pos) + camera.transform.position;
                    glm::vec2 end_world = getCursorWorldPosition(Input::getCursorPos() - viewport_pos) + camera.transform.position;
                    line.setPoints(end_world, start_world);
                }
            }
            else if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) && is_pressed_in_viewport)
            {
                if (current)
                {
                    current->velocity = glm::vec2(0);
                    glm::vec2 offset = getCursorWorldOffset(Input::getCursorOffset());
                    current->transform.position += offset;
                }
                else
                {
                    glm::vec2 start_world = getCursorWorldPosition(start_pos) + camera.transform.position;
                    glm::vec2 end_world = getCursorWorldPosition(Input::getCursorPos() - viewport_pos) + camera.transform.position;
                    line.setPoints(end_world, start_world);

                    glm::vec2 v = start_world - end_world;
                    space.velocity = glm::abs(v) * v;
                }
            }
            else if (Input::getMouseButtonRelease(GLFW_MOUSE_BUTTON_LEFT))
            {
                start_pos = glm::ivec2(-1);

                if (current)
                    current->velocity = current_vel;
            }

            int scroll_dir = Input::getMouseScroll();
            camera.scale += -scroll_dir * (camera.scale * 0.1f);
        }
        else //if not in viewport
        {
            is_pressed_in_viewport = false;
        }

        if (Input::getKeyPress(GLFW_KEY_SPACE))
            to_add = true;

        if (Input::getKeyPress(GLFW_KEY_ESCAPE))
            run_app = false;
    }
    void draw() override
    {
        Shader &shader = Shader::color_shader;
        shader.use();
        shader.setCamera(camera);
        space.draw();
        if (start_pos != glm::ivec2(-1))
            line.draw();
    }

    float radius;
    void drawUI() override
    {
        ImGui::Begin("properties");

        ImGui::DragFloat("G", &space.gravity_const, 1.0f, 0.0f, 100000000.0f);
        ImGui::ColorEdit3("bg color", &clear_color.x);
        ImGui::InputText("name", space.name, sizeof(space.name));
        ImGui::ColorEdit3("color", &space.color.x);
        ImGui::DragFloat("mass", &space.mass, 0.5f, 1.0f, 100000000.0f);
        ImGui::DragFloat("radius", &space.radius, 0.3f, 0.001, 100000000.0f);
        ImGui::DragFloat2("position", &space.pos.x);
        ImGui::DragFloat2("velocity", &space.velocity.x, 1.0f, -100000000.0f, 100000000.0f);

        to_add |= ImGui::Button("add", ImVec2(ImGui::GetContentRegionAvailWidth(), 0));
        ImGui::Checkbox("pause", &pause);

        if (current)
        {
            if (ImGui::TreeNode(current->name))
            {
                radius = current->getRadius();

                ImGui::InputText("name", current->name, sizeof(current->name));
                ImGui::ColorEdit3("color", &current->mesh.color.x);
                ImGui::DragFloat("mass", &current->mass, 0.5f, 1.0f, 100000000.0f);
                ImGui::DragFloat("radius", &radius, 0.3f, 0.001, 100000000.0f);
                ImGui::DragFloat2("position", &current->transform.position.x);
                ImGui::DragFloat2("velocity", &current->velocity.x, 1.0f);
                current->setRadius(radius);
                if (ImGui::Button("remove", ImVec2(ImGui::GetContentRegionAvailWidth(), 0)))
                {
                    space.bodies.erase(std::vector<SpaceBody>::iterator(current));
                    current = nullptr;
                }

                ImGui::TreePop();
            }
        }

        ImGui::End();

        ImGui::Begin("objects");
        for (auto &obj : space.bodies)
        {
            if (ImGui::TreeNode(obj.name))
            {
                radius = obj.getRadius();

                ImGui::InputText("name", obj.name, sizeof(obj.name));
                ImGui::ColorEdit3("color", &obj.mesh.color.x);
                ImGui::DragFloat("mass", &obj.mass, 0.5f, 1.0f, 100000000.0f);
                ImGui::DragFloat("radius", &radius, 0.3f, 0.001, 100000000.0f);
                ImGui::DragFloat2("position", &obj.transform.position.x);
                ImGui::DragFloat2("velocity", &obj.velocity.x, 1.0f, -100000000.0f, 100000000.0f);
                obj.setRadius(radius);
                if (ImGui::Button("remove", ImVec2(ImGui::GetContentRegionAvailWidth(), 0)))
                {
                    space.bodies.erase(std::vector<SpaceBody>::iterator(&obj));
                }

                ImGui::TreePop();
            }
        }
        ImGui::End();
    }

    void cleanup() override {}

    glm::vec2 getCursorWorldPosition(glm::ivec2 c_pos)
    {
        float w = (float)viewport_size.x;
        float h = (float)viewport_size.y;

        float x = ((float)c_pos.x / w - 0.5f) * camera.width * camera.scale;
        float y = -((float)c_pos.y / h - 0.5f) * camera.height * camera.scale;

        return glm::vec2(x, y);
    }

    glm::vec2 getCursorWorldOffset(glm::ivec2 offset)
    {
        float w = (float)viewport_size.x;
        float h = (float)viewport_size.y;

        float x = camera.width * camera.scale * (float)offset.x / w;
        float y = camera.height * camera.scale * (float)offset.y / h;
        return glm::vec2(x, -y);
    }

    bool isInside(glm::ivec2 pos, glm::ivec2 size, glm::ivec2 p)
    {
        return (p.x >= pos.x && p.x <= pos.x + size.x) && (p.y >= pos.y && p.y <= pos.y + size.y);
    }

    bool isPointInsideCircle(glm::vec2 point, glm::vec2 circle_pos, float radius)
    {
        glm::vec2 v = circle_pos - point;
        float distance_square = v.x * v.x + v.y * v.y;
        return distance_square <= (radius * radius);
    }
};