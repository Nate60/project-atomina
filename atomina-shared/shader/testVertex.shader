#version 430 core
layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec4 a_colour;

out vec4 v_colour;

void
main()
{
    gl_Position = vec4(vec3(a_pos, 1.0), 1.0);
    v_colour = a_colour;
}