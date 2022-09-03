#pragma once

#include "application.h"

class MyGame : public Application
{
    Mesh2D<ColoredVertex2D> m;
    Transform t;
    void init() override
    {
        const int quality = 30;
        camera.scale = (float)main_window.getWidth() / 50;

        m = Mesh2D<ColoredVertex2D>::createCircle(0.5f, quality, glm::vec3(1));
    }
    void update() override
    {
        if (Input::getKeyPress(GLFW_KEY_ESCAPE))
            run_app = false;
        // camera update
        if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
            camera.transform.position -= getCursorWorldPosition(Input::getCursorPos()) - getCursorWorldPosition(Input::getCursorLastPos());

        int scroll_dir = Input::getMouseScroll();
        if (scroll_dir < 0)
        {
            if (camera.scale > 3)
                camera.scale += scroll_dir;
        }
        else
            camera.scale += scroll_dir;

        
    }
    void draw() override
    {
        Shader &shader = Shader::color_shader;
        shader.use();
        shader.setCamera(camera);
        shader.setMat3x2("m", t.getMatrix());
        m.draw();
    }
    void cleanup() override
    {
        m.destroy();
    }

    glm::vec2 getCursorWorldPosition(glm::ivec2 c_pos)
    {
        float w = (float)main_window.getWidth();
        float h = (float)main_window.getHeight();

        float x = ((float)c_pos.x / w - 0.5f) * camera.width * camera.scale;
        float y = -((float)c_pos.y / h - 0.5f) * camera.height * camera.scale;

        return glm::vec2(x, y);
    }
};