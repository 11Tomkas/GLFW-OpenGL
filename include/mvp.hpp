#ifndef MVP_HPP
#define MVP_HPP

#include "glm.hpp"

struct MVP
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

#endif