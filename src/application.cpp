#include "application.h"

#include <iostream>

int Application::run()
{
    app_init();
    init();

    float clear_color[3]{0.3f, 0.5f, 0.75f};
    while (run_app && main_window.shouldClose() == 0)
    {
        glViewport(0, 0, main_window.getWidth(), main_window.getHeight());
        glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        update();
        app_update();
        draw();
        main_window.swapBuffers();
    }

    app_cleanup();
    cleanup();

    return 0;
}

void Application::app_init()
{
    main_window.init(800, 800, "openGL");
    Input::init(main_window);
    Shader::initDefaultShader("../resource/shaders/default.vert", "../resource/shaders/default.frag");
    GUI::init(main_window);

    float w = (float)main_window.getWidth();
    float h = (float)main_window.getHeight();

    if (w > h)
    {
        w /= h;
        h = 1.0f;
    }
    else
    {
        h /= w;
        w = 1;
    }
    camera.scale = 2;
    camera.width = w;
    camera.height = h;
    camera.update();
}

void Application::app_update()
{
    main_window.updateSize();
    float w = (float)main_window.getWidth();
    float h = (float)main_window.getHeight();

    if (w > h)
    {
        w /= h;
        h = 1.0f;
    }
    else
    {
        h /= w;
        w = 1;
    }
    camera.width = w;
    camera.height = h;
    camera.update();

    Input::update();
}

void Application::app_cleanup()
{
    GUI::cleanup();
    main_window.cleanup();
}