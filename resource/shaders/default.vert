#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 uv;

uniform mat3x2 m;
uniform mat3x2 v;
uniform mat4 p;

mat3x2 get_camear_space(mat3x2 camera, mat3x2 m)
{
    vec2 og = m[2];
    vec2 c_x = vec2(camera[0].x, camera[1].x);
    vec2 c_y = vec2(camera[0].y, camera[1].y);
    vec2 pos = vec2(dot(c_x, og), dot(c_y, og)) - camera[2];
    mat2 rot = mat2(camera[0].x, -camera[0].y, -camera[1].x, camera[1].y) * mat2(m);
    return mat3x2(rot[0], rot[1], pos);
}

void main() 
{
    gl_Position = p * vec4(get_camear_space(v, m) * vec3(aPos, 1.0f), 0, 1);
    uv = aTexCoord;
}