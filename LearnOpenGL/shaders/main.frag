#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 light_source;
uniform vec3 obj_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

uniform bool isObj;

void main()
{
    if (isObj)
    {

        float ambient_str = 0.1;
        vec3 amb = ambient_str * light_source;

        vec3 norm = normalize(Normal);
        vec3 light_dir = normalize(light_pos - FragPos);

        float diff = max(dot(norm, light_dir), 0.0f);
        vec3 diffuse = diff * light_source;

        float specular_str = 0.5;
        vec3 view_dir = normalize(view_pos - FragPos);
        vec3 reflection_dir = reflect(-light_dir, norm);

        float spec = pow(max(dot(view_dir, reflection_dir), 0.0), 32);
        vec3 specular = specular_str * spec * light_dir;

        vec3 result = (specular + amb + diffuse) * obj_color;
        FragColor = vec4(result, 1.0);
    } else {
        FragColor = vec4(1.0);
    }
}
