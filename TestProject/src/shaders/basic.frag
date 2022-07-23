#version 410 core

in vec3 color;
in vec2 texPos;

out vec4 outColor;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform float mixValue;

void main()
{
    //outColor = mix(texture(u_texture1, texPos), texture(u_texture2, texPos), mixValue);// * vec4(color, 1.0);

    outColor = mix(texture(u_texture1, texPos), texture(u_texture2, texPos), mixValue);
}