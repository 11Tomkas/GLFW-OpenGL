#version 460 core

layout (location = 0) in vec3 iPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    vec4 position = vec4(iPosition, 1.0f);

    gl_Position = uProjection * uView * uModel * position;
}