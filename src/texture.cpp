#include "texture.hpp"

#include "glad\gl.h"
#include "stb_image.h"

Texture::Texture()
    : m_name{ 0 }
{
    glGenTextures(1, &m_name);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_name);
}

void Texture::bind(unsigned int target) const
{
    glBindTexture(target, m_name);
}

void Texture::unbind(unsigned int target) const
{
    glBindTexture(target, 0);
}

void Texture::image2D(unsigned int target, int level, int internalFormat, int border, unsigned int format, unsigned int type, const char* fileName) const
{
    int width;
    int height;
    int channels;
    unsigned char* data{ stbi_load(fileName, &width, &height, &channels, 0) };

    glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
    stbi_image_free(data);
}

void Texture::generateMipmap(unsigned int target)
{
    glGenerateMipmap(target);
}