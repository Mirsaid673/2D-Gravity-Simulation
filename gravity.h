#pragma once

#include "application.h"
#include "space.h"

class MyGame : public Application
{
    Space space;
    bool to_add = false;

    void init() override
    {
        camera.scale = (float)viewport_size.x / 50;
    }
    void update() override
    {
        if (to_add)
        {
            space.add();
        }

        space.update_physics(1.0 / 60.0);

        if (Input::getMouseButtonRelease(GLFW_MOUSE_BUTTON_LEFT))
            if (isInside(viewport_pos, viewport_size, Input::getCursorPos()))
                space.pos = getCursorWorldPosition(Input::getCursorPos() - viewport_pos) + camera.transform.position;

        if (Input::getKeyPress(GLFW_KEY_ESCAPE))
            run_app = false;
        // camera update
        if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
            if (isInside(viewport_pos, viewport_size, Input::getCursorPos()))
                camera.transform.position -= getCursorWorldOffset(Input::getCursorOffset());

        int scroll_dir = Input::getMouseScroll();

        camera.scale += -scroll_dir * (camera.scale * 0.1f);
    }
    void draw() override
    {
        Shader &shader = Shader::color_shader;
        shader.use();
        shader.setCamera(camera);
        space.draw();
    }

    void drawUI() override
    {
        ImGui::Begin("properties");

        ImGui::DragFloat("G", &space.gravity_const, 1.0f, 0.0f, 100000000.0f);
        ImGui::ColorEdit3("color", &space.color.x);
        ImGui::DragFloat("mass", &space.mass, 0.5f, 1.0f, 100000000.0f);
        ImGui::DragFloat("radius", &space.radius, 0.3f, 0.001, 100000000.0f);
        ImGui::DragFloat2("position", &space.pos.x);
        ImGui::DragFloat2("velocity", &space.velocity.x);

        to_add = ImGui::Button("add", ImVec2(ImGui::GetWindowContentRegionWidth(), 0));

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
};