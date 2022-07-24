#version 330 core
// NOTE: Always start with 0 !!!
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexPos;

out vec3 color;
out vec2 texPos;

uniform float u_scaleFactor;

void main()
{
    color = aColor;
    texPos = aTexPos;
    //gl_Position = vec4(aPos.x * u_scale, aPos.y * u_scale, aPos.z * u_scale, 1.0);
    gl_Position = vec4(aPos * u_scaleFactor, 1.0);
    // NOTE: Let's imagine, that our position values specify a cube with size 1;
    // Then by multiplying each position value by some factor, we can adjust final rectangle size,
    // e.g. When we multiply eash position by 0.5, then each of them turns to be half way closer to origin, then originally;
    // And vice versa: If we multiply positions by, let's take, 2, then they'll be twice as far as originally.
}