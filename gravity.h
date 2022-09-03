#pragma once

#include "application.h"

#include <memory>
#include <array>

class MyGame : public Application
{
    

    void init() override
    {
        camera.scale = (float)main_window.getWidth() / 50.f;
    }
    void update() override
    {
        if (Input::getKeyPress(GLFW_KEY_ESCAPE))
            run_app = false;

        
    }
    void draw() override
    {
        Shader &shader = Shader::default_shader;
        shader.use();
        shader.setCamera(camera);
        
    }
    void cleanup() override {}
};