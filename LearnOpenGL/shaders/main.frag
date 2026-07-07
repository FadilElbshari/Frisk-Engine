#version 330 core

out vec4 FragColor;
// in vec3 color;
in float z_pos;

void main()
{
    vec3 color = vec3((z_pos + 1) / 2);
    FragColor = vec4(color, 1.0);
}
