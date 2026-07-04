#version 330 core

layout(location = 0) in vec3 aPos;

// per instance data
layout(location = 1) in vec3 aTranslation;
layout(location = 2) in vec3 aSize;
layout(location = 3) in vec3 aColor;

out vec3 color;

uniform float time;

uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main()
{
    color = aColor;
    vec3 worldPos = (aPos) * aSize + aTranslation;

    gl_Position = proj_matrix * vec4(worldPos, 1.0);
}
