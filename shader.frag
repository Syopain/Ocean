#version 330 core
out vec4 frag_color;

in vec3 our_color;
in vec2 tex_coord;
in vec3 normal;
in vec3 frag_pos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_value;
uniform vec3 camera;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

Material material;

void main()
{
    //material.ambient = vec3(0.19225, 0.19225, 0.19225);
    //material.diffuse = vec3(0.50754, 0.50754, 0.50754);
    //material.specular = vec3(0.508273, 0.508273, 0.508273);
    material.ambient = 0.6 * vec3(0.05f, 0.3f, 0.42f);
    material.diffuse = vec3(0.05f, 0.3f, 0.42f);
    material.specular = vec3(1.0f, 1.0f, 1.0f);
    material.shininess = 10;

    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 light_dir = normalize(vec3(0.0f, 800.0f, 0.0f));

    vec3 ambient = light_color * material.ambient;

    vec3 norm = normalize(normal);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light_color * (diff * material.diffuse);

    vec3 view_dir = normalize(camera - frag_pos);
    vec3 haflway_dir = normalize(light_dir + view_dir);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(haflway_dir, norm), 0.0f), material.shininess * 128);
    //spec = pow(max(dot(reflect_dir, view_dir), 0.0f), material.shininess * 128);
    vec3 specular = light_color * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;

    frag_color = vec4(ambient + diffuse + specular, 0.5f);
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
