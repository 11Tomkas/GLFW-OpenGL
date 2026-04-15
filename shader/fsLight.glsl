#version 460 core

out vec4 oFragment;

void main()
{
    vec3 color = vec3(1.0f, 1.0f, 1.0f);

    oFragment = vec4(color, 1.0f);
}