#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 color;

uniform float time;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;


void main()
{
    color = aColor;
    gl_Position = proj_matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
