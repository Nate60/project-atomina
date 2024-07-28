#version 430 core
out vec4 FragColor;

in vec4 v_colour;

void
main()
{
    FragColor = v_colour;
}