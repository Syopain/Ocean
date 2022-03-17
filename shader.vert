#version 330 core
layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_tex_coord;
out vec3 our_color;
out vec2 tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform vec3 camera;

void main()
{
    float w = 1;
    vec2 offset = a_pos;
    offset.x += camera.x;
    offset.y += camera.z;
    float y = 0.5 * sin(dot(vec2(1.0f, 0.0f), offset) + time * 5);
    y += 0.5 * sin(dot(vec2(0.0f, 1.0f), offset) + time * 5);
    y += 0.5 * sin(dot(vec2(0.5f, 0.5f), offset) * 0.5 + time * 5);
    gl_Position = projection * view * model * vec4(offset.x, y, offset.y, 1.0f);
    //gl_Position = projection * view * model * vec4(offset.x, 0.0f, offset.y, 1.0f);
    our_color = a_color;
    tex_coord = a_tex_coord;
}
