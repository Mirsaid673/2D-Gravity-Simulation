#pragma once

#include "texture.h"

class Framebuffer
{
private:
    Texture texture;
    GLuint ID;

public:
    void create(int w, int h);

    void bind();
    void unbind();
    void resize(int w, int h);

    void destroy();

    GLuint getTexID() const { return texture.getID(); }
    void useTex() const { texture.use(); }
};