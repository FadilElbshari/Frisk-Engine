#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

out vec3 result;

uniform float time;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 model_matrix;

uniform vec3 light_source;
uniform vec3 obj_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main()
{

    Normal = mat3(transpose(inverse(model_matrix))) * aNormal;
    FragPos = vec3(model_matrix * vec4(aPos, 1.0));

    float ambient_str = 0.1;
    vec3 amb = ambient_str * light_source;

    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(light_pos - FragPos);

    float diff = max(dot(norm, light_dir), 0.0f);
    vec3 diffuse = diff * light_source;

    float specular_str = 1.0;
    vec3 view_dir = normalize(view_pos - FragPos);
    vec3 reflection_dir = reflect(-light_dir, norm);

    float spec = pow(max(dot(view_dir, reflection_dir), 0.0), 32);
    vec3 specular = specular_str * spec * light_dir;

    result = (specular + amb + diffuse) * obj_color;

    vec4 final_pos = proj_matrix * view_matrix * model_matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    gl_Position = final_pos;
}
