#version 460 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTextureCoord;

out vec3 fNormal;
out vec2 fTextureCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    vec4 position = vec4(iPosition, 1.0f);

    gl_Position = uProjection * uView * uModel * position;
    fNormal = iNormal;
    fTextureCoord = iTextureCoord;
}