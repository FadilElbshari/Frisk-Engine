#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

// out vec3 color;
out float z_pos;

uniform float time;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 model_matrix;

void main()
{
    // color = aColor;
    vec4 final_pos = proj_matrix * view_matrix * model_matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    z_pos = final_pos.z;
    gl_Position = final_pos;
}
