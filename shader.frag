#version 330 core
out vec4 frag_color;

in vec2 tex_coord;
in vec2 bump_coord_1;
in vec2 bump_coord_2;
in vec3 frag_pos;
in vec3 screen_pos;
in vec3 normal;
in mat3 TBN;
in float max_wave_height;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 camera;
uniform float time;
uniform vec3 color;
uniform int status;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 subsurface;
    vec3 fresnel;
    float shininess;
};

Material material;

struct Light {
    vec3 color;
    vec3 dir;
};


float sss_intensity(vec3 lightDir, vec3 viewDir, vec3 normal, float distortion, float waveHeight, float SSSMask)
{
    if (status == 0) return 0;
    vec3 h = normalize(viewDir + normal * distortion);
    float I = pow(clamp(dot(h, -lightDir), 0, 1), 4.0) * pow(waveHeight, 1) * SSSMask;

    // Fast Subsurface Scattering
    if (status == 2) {
    //if (screen_pos.x > 0) {
        h = normalize(lightDir + normal * distortion);
        I = pow(clamp(dot(viewDir, -h), 0, 1), 4.0) * pow(waveHeight, 1) * SSSMask;
        return I;
    }

/*
    vec3 ambientDir = -viewDir;
    ambientDir.y = dot(viewDir, normalize(vec3(viewDir.x, 0, viewDir.z)));
    ambientDir = normalize(ambientDir);
    I += pow(clamp(dot(h, -ambientDir), 0, 1), 4.0) * waveHeight * SSSMask * 0.2;
*/
    return I;

}

float fresnel_intensity(vec3 v, vec3 norm)
{
    float airRefractiveIndex = 1.0f;
    float waterRefractiveIndex = 1.33f;

    float F0 = (airRefractiveIndex - waterRefractiveIndex) / (airRefractiveIndex + waterRefractiveIndex);
    F0 *= F0;
    return  F0 + (1 - F0) * pow((1.0 - clamp(abs(dot(v, norm)), 0, 1)), 5);
}

void main()
{
    material.ambient = 0.5 * color;
    //material.diffuse = 1 * texture(texture2, tex_coord).rgb;
    material.diffuse = 0.2 * color;
    //material.subsurface = 1 * vec3(0.3f, 1.0f, 0.9f);
    material.subsurface = 1.6 * (color + vec3(0.1, 0.5, 0.3));
    material.specular = vec3(1.0f, 1.0f, 1.0f);
    //material.fresnel =  0.5 * vec3(0.5, 0.8f, 0.9f);
    material.fresnel =  0.5 * vec3(1.0, 1.0, 1.0);
    material.shininess = 12;

    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 light_dir = normalize(vec3(0.0f, 400.0f, -800.0f));

    vec3 bump = mix(texture(texture1, bump_coord_1), texture(texture1, bump_coord_2), 0.5).rgb;
    bump = normalize(bump * 2.0 - 1.0);
    bump = normalize(TBN * bump);
    vec3 norm = normalize(normal);

    vec3 ambient = light_color * material.ambient;// * (frag_pos.y + max_wave_height) / (max_wave_height * 2);

    float diff = max(dot(normalize(0.2*bump + norm), light_dir), 0.0);
    vec3 diffuse = light_color * (diff * material.diffuse);

    vec3 view_dir = normalize(camera - frag_pos);
    vec3 haflway_dir = normalize(light_dir + view_dir);
    float spec = pow(max(dot(haflway_dir, bump), 0.0f), material.shininess * 128);
    vec3 specular = light_color * (spec * material.specular);

    bump = normalize(bump + norm);
    float fresl = fresnel_intensity(view_dir, bump);

    float sss = (1-fresl) * sss_intensity(light_dir, view_dir, bump, 0.5, (frag_pos.y + max_wave_height) / (max_wave_height * 2), 1);
    vec3 subsurface = sss * material.subsurface;

    vec3 fresnel = fresl * material.fresnel;

    vec3 result = ambient + diffuse + specular + subsurface + fresnel;
    //vec3 result = ambient + diffuse + specular + fresnel;// + subsurface;
    //if (screen_pos.x > 0) result += subsurface;

    frag_color = vec4(result, 1.0f);
    //frag_color = vec4(color, 1);
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
