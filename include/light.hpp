#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "cube.hpp"

struct DirectionLight
{
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class PointLight
    : public Cube
{
    public:
        float constant;
        float linear;
        float quadratic;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        PointLight();
        PointLight(const PointLight&) = delete;
        PointLight(PointLight&&) = delete;
        ~PointLight() = default;
        PointLight& operator=(const PointLight&) = delete;
        PointLight& operator=(PointLight&&) = delete;

        void draw(const Shader& shader, MVP& mvp);
};

struct SpotLight
{
    glm::vec3 position;
    glm::vec3 direction;
    float innerCutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct Light
{
    DirectionLight directionLight;
    PointLight pointLights[4];
    SpotLight spotLight;
};

#endif