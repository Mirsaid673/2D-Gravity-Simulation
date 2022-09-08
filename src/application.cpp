#include "application.h"

#include <iostream>

int Application::run()
{
    app_init();
    init();

    while (run_app && main_window.shouldClose() == 0)
    {
        update();

        framebuffer.resize(viewport_size.x, viewport_size.y);
        framebuffer.bind();

        glViewport(0, 0, viewport_size.x, viewport_size.y);
        glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        camera.width = viewport_size.x;
        camera.height = viewport_size.y;
        camera.update();
        draw();

        framebuffer.unbind();

        glViewport(0, 0, main_window.getWidth(), main_window.getHeight());
        glClearColor(app_clear_color[0], app_clear_color[1], app_clear_color[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GUI::newFrame();
        ImGui::Begin("scene");

        ImVec2 s = ImGui::GetContentRegionAvail();
        viewport_size = glm::ivec2(s.x, s.y);
        viewport_pos.x = (ImGui::GetWindowPos().x + ImGui::GetCursorPos().x);
        viewport_pos.y = (ImGui::GetWindowPos().y + ImGui::GetCursorPos().y);
        ImGui::Image(reinterpret_cast<ImTextureID>(framebuffer.getTexID()), s, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();

        drawUI();
        GUI::renderFrame();

        app_update();
    }

    app_cleanup();
    cleanup();

    return 0;
}

void Application::app_init()
{
    main_window.init(800, 800, "openGL");
    Input::init(main_window);
    Shader::texture_shader.load("../resource/shaders/texture.vert", "../resource/shaders/texture.frag");
    Shader::color_shader.load("../resource/shaders/color.vert", "../resource/shaders/color.frag");
    GUI::init(main_window);

    float w = (float)main_window.getWidth();
    float h = (float)main_window.getHeight();

    camera.scale = 1;
    camera.width = w;
    camera.height = h;

    viewport_pos = glm::ivec2(0);
    viewport_size.x = w;
    viewport_size.y = h;

    framebuffer.create(w, h);
}

void Application::app_update()
{
    main_window.updateSize();
    Input::update();
    main_window.swapBuffers();
}

void Application::app_cleanup()
{
    GUI::cleanup();
    framebuffer.destroy();
    main_window.cleanup();
}