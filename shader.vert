#version 330 core
layout (location = 0) in vec2 a_pos;
out vec2 tex_coord_1;
out vec2 tex_coord_2;
out vec3 frag_pos;
out vec3 tangent;
out vec3 bitangent;
out vec3 normal;
out mat3 TBN;
out float max_wave_height;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform vec3 camera;
uniform sampler2D texture;

vec3 p1;
vec3 p2;

void sinusoidsWave(vec2 p, float amplitude, float w, vec2 direction, float speed, float offset);
void gerstnerWave(vec2 p, float amplitude, float q, float w, vec2 direction, float speed, float offset);
void tbn();

float texture_size = 80;
float delta = 0.1;

void main()
{
    max_wave_height = 0;
    vec2 offset = a_pos;
    offset.x += camera.x;
    offset.y += camera.z;
    gl_Position = vec4(offset.x, 0.0f, offset.y, 1.0f);
    p1 = p2 = gl_Position.xyz;
    p1.x += delta;
    p2.z += delta;

    normal = vec3(0, 1, 0);

    float speed = 5;

    gerstnerWave(offset, 0.2, 0.2f, 25, vec2(1.0, 1.2), speed, 22.1);
    gerstnerWave(offset, 0.2, 0.2f, 16, vec2(1.0, 0.6), speed, 11.4);
    gerstnerWave(offset, 0.2, 0.2f, 15, vec2(1.0, 1.8), speed, 41.5);
    gerstnerWave(offset, 0.2, 0.2f, 15, vec2(1.0, 0.0), speed, 10.2);

    gerstnerWave(offset, 0.1, 0.1f, 37, vec2(-0.27, 0.68), speed, 3.2);
    gerstnerWave(offset, 0.1, 0.1f, 25, vec2(0.16, -0.92), speed, 2.1);
    gerstnerWave(offset, 0.1, 0.1f, 54, vec2(0.66, 0.39), speed, 5.4);
    gerstnerWave(offset, 0.1, 0.1f, 56, vec2(-0.23, 0.67), speed, 12.0);
    gerstnerWave(offset, 0.1, 0.1f, 39, vec2(0.35, 0.81), speed, 41.4);
    gerstnerWave(offset, 0.1, 0.1f, 39, vec2(-0.44, 0.86), speed, 39.1);
    gerstnerWave(offset, 0.1, 0.1f, 51, vec2(0.31, -0.44), speed, 39.4);
    gerstnerWave(offset, 0.1, 0.1f, 12, vec2(0.37, 0.47), speed, 14.1);
    gerstnerWave(offset, 0.1, 0.1f, 17, vec2(-0.88, 0.22), speed, 24.5);

    float f = time / 20;
    tex_coord_1 = gl_Position.xz / texture_size + vec2(f, 0.0);
    tex_coord_2 = gl_Position.xz / texture_size + vec2(0.0, f);

    tbn();
    frag_pos = vec3(model * gl_Position);
    gl_Position = projection * view * model * gl_Position;
}

void sinusoidsWave(vec2 p, float amplitude, float l, vec2 direction, float speed, float offset)
{
    gerstnerWave(p, amplitude, 0, l, direction, speed, offset);
}

void gerstnerWave(vec2 p, float amplitude, float q, float l, vec2 direction, float speed, float offset)
{
    max_wave_height += amplitude;
    direction = normalize(direction);

    float w = 2 * acos(-1) / l;
    float c = cos(w * dot(direction, p) + speed * time + offset);
    float s = sin(w * dot(direction, p) + speed * time + offset);

    normal -= vec3(direction.x * w * amplitude * c,
                  q * s,
                  direction.y * w * amplitude * c);

    gl_Position.xyz += vec3(q / w * direction.x * c,
                amplitude * s,
                q / w * direction.y * c);


    float c1 = cos(w * dot(direction, p + vec2(delta, 0.0)) + speed * time + offset);
    float s1 = sin(w * dot(direction, p + vec2(delta, 0.0)) + speed * time + offset);
    p1 += vec3(q / w * direction.x * c1,
                amplitude * s1,
                q / w * direction.y * c1);

    float c2 = cos(w * dot(direction, p + vec2(0.0, delta)) + speed * time + offset);
    float s2 = sin(w * dot(direction, p + vec2(0.0, delta)) + speed * time + offset);
    p2 += vec3(q / w * direction.x * c2,
                amplitude * s2,
                q / w * direction.y * c2);

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

void tbn()
{
    vec3 edge1 = p1 - gl_Position.xyz;
    vec3 edge2 = p2 - gl_Position.xyz;
    vec2 deltaUV1 = vec2(delta / texture_size, 0.0);
    vec2 deltaUV2 = vec2(0.0, delta / texture_size);

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV2.y);
    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent = normalize(tangent);
    //normal = mat3(transpose(inverse(model))) * normal;
    bitangent = normalize(cross(tangent, normal));
    TBN = mat3(tangent, bitangent, normal);
}
