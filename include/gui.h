#pragma once

#include "window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class GUI
{
public:
    static ImGuiIO *io;
    static void init(const Window &window);
    static void cleanup();

    static void newFrame();
    static void renderFrame();
};