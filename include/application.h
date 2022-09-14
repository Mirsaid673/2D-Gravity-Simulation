#pragma once

#include "window.h"
#include "mesh2D.h"
#include "shader.h"
#include "model.h"
#include "camera2D.h"
#include "framebuffer.h"
#include "input.h"
#include "gui.h"

class Application
{
private:
    glm::vec3 app_clear_color = glm::vec3(0.41015625, 0.41015625, 0.41015625);

    void app_init();
    void app_update();

protected:
    virtual void init(){};
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void drawUI() = 0;
    virtual void cleanup(){};

    void app_cleanup();

public:
    int run();

protected:
    Window main_window;
    Camera2D camera;
    Framebuffer framebuffer;
    glm::vec3 clear_color;
    glm::ivec2 viewport_pos;
    glm::ivec2 viewport_size;

    bool run_app = true;
};