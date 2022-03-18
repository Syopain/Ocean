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

float sinusoidsWave(vec2 p, float amplitude, float w, vec2 direction, float speed);
vec3 gerstnerWave(vec2 p, float amplitude, float q, float w, vec2 direction, float speed);

void main()
{
    float l = 10;

    vec2 offset = a_pos;
    offset.x += camera.x;
    offset.y += camera.z;
    gl_Position = vec4(offset.x, 0.0f, offset.y, 1.0f);

    gl_Position.xyz += gerstnerWave(offset, 0.5f, 1, l*2, vec2(0.2f, 0.1f), 5);
    gl_Position.xyz += gerstnerWave(offset, 0.5f, 2, l, vec2(0.2f, 0.7f), 5);
    gl_Position.xyz += gerstnerWave(offset, 0.5f, 2, l*3, vec2(0.5f, 0.5f), 5);
    gl_Position.xyz += gerstnerWave(offset, 0.5f, 1, l*1.5, vec2(1.0f, 0.2f), 5);

    gl_Position = projection * view * model * gl_Position;

    our_color = a_color;
    tex_coord = a_tex_coord;
}

float sinusoidsWave(vec2 p, float amplitude, float l, vec2 direction, float speed)
{
    return amplitude * cos(dot(normalize(direction) * 2 * acos(-1) / l, p) + speed * time);
}

vec3 gerstnerWave(vec2 p, float amplitude, float q, float l, vec2 direction, float speed)
{
    direction = normalize(direction);
    return vec3(- q * amplitude * direction.x * sin(dot(direction, p) * 2 * acos(-1) / l + speed * time),
                sinusoidsWave(p, amplitude, l, direction, speed),
                - q * amplitude * direction.y * sin(dot(direction, p) * 2 * acos(-1) / l + speed * time));
}
