#version 330 core
// NOTE: Always start with 0 !!!
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexPos;

out vec3 color;
out vec2 texPos;

uniform float u_scaleFactor;
uniform vec2 u_translationFactor;

void main()
{
    color = aColor;
    texPos = aTexPos;

    vec3 pos = aPos * u_scaleFactor;
    pos = pos + vec3(u_translationFactor, 0.0f);
    gl_Position = vec4(pos, 1.0f);
}