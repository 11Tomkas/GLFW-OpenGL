#version 460 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iColor;
layout (location = 2) in vec3 iNormal;
layout (location = 3) in vec2 iTexCoord;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    vec4 position = vec4(iPosition, 1.0f);

    gl_Position = uProjection * uView * uModel * position;

    fPosition = vec3(uModel * position);
    fNormal = mat3(uModel) * iNormal;
    fTexCoord = iTexCoord;
}