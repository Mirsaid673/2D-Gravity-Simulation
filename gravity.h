#pragma once

#include "application.h"
#include "space.h"

class MyGame : public Application
{
    Space space;
    bool to_add = false;
    void init() override
    {
        const int quality = 30;
        camera.scale = (float)main_window.getWidth() / 50;
        space.color = glm::vec3(0.5);
    }
    void update() override
    {
        if(to_add)
        {
            space.add();
        }

        space.update_physics(1.0/60.0);
        
        if (GUI::io->MouseReleased[0])
            space.pos = getCursorWorldPosition(Input::getCursorPos()) + camera.transform.position;

        if (Input::getKeyPress(GLFW_KEY_ESCAPE))
            run_app = false;
        // camera update
        if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
            camera.transform.position -= getCursorWorldOffset(Input::getCursorOffset());

        int scroll_dir = Input::getMouseScroll();
        if (scroll_dir > 0)
        {
            if (camera.scale > 2)
                camera.scale -= scroll_dir;
        }
        else
            camera.scale -= scroll_dir;
    }
    void draw() override
    {
        Shader &shader = Shader::color_shader;
        shader.use();
        shader.setCamera(camera);
        space.draw();

        GUI::newFrame();

        ImGui::Begin("properties");

        ImGui::InputFloat("G", &space.gravity_const);
        ImGui::ColorEdit3("color", &space.color.x);
        ImGui::InputFloat("mass", &space.mass);
        ImGui::InputFloat("radius", &space.radius);
        ImGui::InputFloat2("position", &space.pos.x);
        ImGui::InputFloat2("velocity", &space.velocity.x);
        ImGui::InputFloat2("acceleration", &space.acceleration.x);

        to_add = ImGui::Button("add");

        ImGui::End();
        GUI::renderFrame();
    }
    void cleanup() override {}

    glm::vec2 getCursorWorldPosition(glm::ivec2 c_pos)
    {
        float w = (float)main_window.getWidth();
        float h = (float)main_window.getHeight();

        float x = ((float)c_pos.x / w - 0.5f) * camera.width * camera.scale;
        float y = -((float)c_pos.y / h - 0.5f) * camera.height * camera.scale;

        return glm::vec2(x, y);
    }

    glm::vec2 getCursorWorldOffset(glm::ivec2 offset)
    {
        float w = (float)main_window.getWidth();
        float h = (float)main_window.getHeight();

        float x = camera.width * camera.scale * (float)offset.x / w;
        float y = camera.height * camera.scale * (float)offset.y / h;
        return glm::vec2(x, -y);
    }
};