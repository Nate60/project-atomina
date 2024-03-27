#version 430 core
out vec4 FragColor;

in vec4 v_colour;
in vec2 v_texCoord;

uniform sampler2D ourTexture;

void
main()
{
    FragColor = texture(ourTexture, v_texCoord);
}