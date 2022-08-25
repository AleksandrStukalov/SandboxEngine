#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;

//out vec2 texPos;

uniform mat4 u_transformation;

void main()
{
    //texPos = aTexPos;

    gl_Position = u_transformation * vec4(aPos, 1.0f);
}