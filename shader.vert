#version 330 core
layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_tex_coord;
out vec3 our_color;
out vec2 tex_coord;
out vec3 normal;
out vec3 frag_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform vec3 camera;

void sinusoidsWave(vec2 p, float amplitude, float w, vec2 direction, float speed);
void gerstnerWave(vec2 p, float amplitude, float q, float w, vec2 direction, float speed);

void main()
{
    float l = 10;

    vec2 offset = a_pos;
    offset.x += camera.x;
    offset.y += camera.z;
    gl_Position = vec4(offset.x, 0.0f, offset.y, 1.0f);

    normal = vec3(0, 1, 0);

    gerstnerWave(offset, 3, 0.2f, 120, vec2(1.0, 1.0), 5);
    gerstnerWave(offset, 2, 0.2f, 62, vec2(1.0, 0.6), 5);
    gerstnerWave(offset, 1, 0.2f, 36, vec2(1.0, 1.3), 5);
    gerstnerWave(offset, 2, 0.2f, 60, vec2(1.0, 0.0), 5);

    frag_pos = vec3(model * gl_Position);
    gl_Position = projection * view * model * gl_Position;

    normal = mat3(transpose(inverse(model))) * normal;
    our_color = a_color;
    tex_coord = a_tex_coord;
}

void sinusoidsWave(vec2 p, float amplitude, float l, vec2 direction, float speed)
{
    gerstnerWave(p, amplitude, 0, l, direction, speed);
}

void gerstnerWave(vec2 p, float amplitude, float q, float l, vec2 direction, float speed)
{
    direction = normalize(direction);

    float w = 2 * acos(-1) / l;
    float c = cos(w * dot(direction, p) + speed * time);
    float s = sin(w * dot(direction, p) + speed * time);

    normal -= vec3(direction.x * w * amplitude * c,
                  q * s,
                  direction.y * w * amplitude * c);

    gl_Position.xyz += vec3(q / w * direction.x * c,
                amplitude * s,
                q / w * direction.y * c);

/*
    q /= amplitude;
    q /= w;
    normal -= vec3(direction.x * w * amplitude * c,
                  q * w * amplitude * s,
                  direction.y * w * amplitude * c);
    gl_Position.xyz += vec3(q * amplitude * direction.x * c,
                amplitude * s,
                q * amplitude * direction.y * c);
*/
}
