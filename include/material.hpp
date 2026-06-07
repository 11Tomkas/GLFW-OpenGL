#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "texture.hpp"

struct Material
{
    Texture diffuse;
    Texture specular;
    float shininess;
};

#endif