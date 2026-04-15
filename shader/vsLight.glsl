#version 460 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iColor;
layout (location = 2) in vec3 iNormal;
layout (location = 3) in vec2 iTextureCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    vec4 position = vec4(iPosition, 1.0f);

    gl_Position = uProjection * uView * uModel * position;
}