#version 410 core
// NOTE: Always start with 0 !!!
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

void main()
{
    color = aColor;
    gl_Position = vec4(aPos, 1.0);
}