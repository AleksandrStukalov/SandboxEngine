#version 330 core


out vec4 outColor;

uniform vec3 u_color;

void main()
{
	outColor = vec4(u_color, 1.0f);
}