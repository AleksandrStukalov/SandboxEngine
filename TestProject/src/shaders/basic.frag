#version 330 core

in vec2 texPos;

out vec4 outColor;

uniform sampler2D u_texture;

void main()
{
    outColor = texture(u_texture, texPos);
}