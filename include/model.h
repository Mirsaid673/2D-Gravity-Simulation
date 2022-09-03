#pragma once

#include "sprite.h"
#include "shader.h"
#include "transform.h"

class Model
{
private:
    const Shader *shader;

public:
    Transform transform;
    Sprite sprite;

    void setShader(const Shader *s) { shader = s; }
    const Shader *getShader() { return shader; }

    void draw()
    {
        shader->setMat3x2("m", transform.getMatrix());
        shader->setScalar("tex", 0);
        sprite.draw();
    }

    Model() : shader(&Shader::default_shader){}
};