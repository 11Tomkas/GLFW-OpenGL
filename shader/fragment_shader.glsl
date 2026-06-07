#version 460 core

in vec3 fNormal;
in vec2 fTextureCoord;

out vec4 oColor;

uniform sampler2D uDiffuse;
uniform sampler2D uSpecular;

void main()
{
    vec3 color = texture(uDiffuse, fTextureCoord).rgb;

    oColor = vec4(color, 1.0f);
}