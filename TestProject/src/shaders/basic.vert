#version 330 core
// NOTE: Always start with 0 !!!
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexPos;

out vec3 color;
out vec2 texPos;

void main()
{
    color = aColor;
    texPos = aTexPos;
    gl_Position = vec4(aPos, 1.0);
}