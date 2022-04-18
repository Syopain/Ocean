#version 330 core
out vec4 frag_color;

in vec2 tex_coord_1;
in vec2 tex_coord_2;
in vec3 frag_pos;
in vec3 screen_pos;
in vec3 normal;
in mat3 TBN;
in float max_wave_height;

uniform sampler2D texture;
uniform vec3 camera;
uniform float time;
uniform vec3 color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 subsurface;
    float shininess;
};

Material material;

struct Light {
    vec3 color;
    vec3 dir;
};


float sss_intensity(vec3 lightDir, vec3 viewDir, vec3 normal, float distortion, float waveHeight, float SSSMask)
{
    vec3 h = normalize(lightDir + normal * distortion);
    return pow((dot(viewDir, -h) + 1) / 2, 4.0) * waveHeight * SSSMask;
    //return pow(clamp(dot(viewDir, -h), 0, 1), 1) * waveHeight * SSSMask;
}

float fresnel_intensity(vec3 v, vec3 norm)
{
    float _AirRefractiveIndex = 1.0f;
    float _WaterRefractiveIndex = 1.33f;

    float R_0 = (_AirRefractiveIndex - _WaterRefractiveIndex) / (_AirRefractiveIndex + _WaterRefractiveIndex);
    R_0 *= R_0;
    return  R_0 + (1.0 - R_0) * pow((1.0 - clamp(dot(v, norm), 0, 16)), 4);
}

void main()
{
    material.ambient = 0.2 * color;
    material.diffuse = 1.0 * color;
    material.subsurface = 1.0 * vec3(0.3f, 0.9f, 1.0f);
    material.specular = vec3(1.0f, 1.0f, 1.0f);
    material.shininess = 8;

    //vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    //vec3 light_dir = normalize(vec3(0.0f, 400.0f, -800.0f));

    Light light[2];
    light[0].color = vec3(1.0f, 1.0f, 1.0f);
    light[0].dir = normalize(vec3(0.0f, 100.0f, -200.0f));

    vec3 bump = mix(texture(texture, tex_coord_1), texture(texture, tex_coord_2), 0.5).rgb;
    bump = normalize(bump * 2.0 - 1.0);
    bump = normalize(TBN * bump);
    vec3 norm = normalize(normal);

    float PI = acos(-1);
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 subsurface;
    vec3 fresnel;

    for (int i = 0; i < 1; ++i) {
        ambient = light[i].color * material.ambient * (frag_pos.y + max_wave_height) / (max_wave_height * 2);

        float diff = max(dot(normalize(1 * norm + bump * 0), light[i].dir), 0.0);
        diffuse += light[i].color * (diff * material.diffuse);

        vec3 view_dir = normalize(camera - frag_pos);
        vec3 haflway_dir = normalize(light[i].dir + view_dir);
        float spec = pow(max(dot(haflway_dir, bump), 0.0f), material.shininess * 128);
        specular += light[i].color * (spec * material.specular);

        if (true || i == 0) // Removing this causes bugs, which I don't understand why
        subsurface += sss_intensity(light[i].dir, view_dir, bump, 1.0, (frag_pos.y + max_wave_height) / (max_wave_height * 2), 1) * material.subsurface;

        fresnel += fresnel_intensity(view_dir, bump) * vec3(0.5f, 0.8f, 0.9) * 0.05;
    }


    vec3 result = ambient + diffuse + specular + subsurface + fresnel;

    frag_color = vec4((norm + 1)/2, 1);  // normal
    frag_color = vec4(result, 0.5f);
}

/*
void main()
{
    //frag_color = mix(texture(texture1, tex_coord), texture(texture2, tex_coord), mix_value);
    //frag_color = vec4(0.5f * (normal + vec3(1.0f, 1.0f, 1.0f)), 1.0f);

    vec3 color = vec3(0.0f, 0.27f, 0.42f);
    //vec3 color = vec3(0.0f, 0.0f, 0.0f);

    vec3 light_dir = normalize(vec3(0.0f, 800.0f, -1000.0f));
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light_color;
    float diff = max(dot(normalize(normal), light_dir), 0.0f);
    vec3 diffuse = diff * light_color;
    float specularStrength = 1.0f;
    vec3 view_dir = normalize(camera - frag_pos);
    vec3 reflect_dir = reflect(-normalize(light_dir), normalize(normal));
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 64);
    vec3 specular = specularStrength * spec * light_color;
    //frag_color = vec4(specular + (ambient + diffuse) * color, 1.0f);
    frag_color = vec4(ambient + specular + diffuse * color, 1.0f);
    //frag_color = vec4((diffuse) * color, 1.0f);
}
*/
