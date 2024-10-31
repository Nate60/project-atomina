#version 430 core
layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec4 a_colour;
layout(location = 2) in vec2 a_texCoord;

out vec4 v_colour;
out vec2 v_texCoord;

uniform mat3 u_camera;
uniform mat3 u_translate;
uniform mat3 u_scale;
uniform mat3 u_rot;
uniform mat3 u_textureRegion;
uniform mat3 u_texturePos;
uniform mat3 u_textureCamera;
void
main()
{

    gl_Position = vec4((inverse(u_camera) * u_translate * u_scale * u_rot * vec3(a_pos, 1.0)), 1.0);
    v_colour = a_colour;
    vec3 srcRegion = inverse(u_textureCamera) * u_texturePos * u_textureRegion * vec3(a_texCoord, 1.0);
    v_texCoord = vec2(srcRegion.x, srcRegion.y);
}