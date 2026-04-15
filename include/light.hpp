#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "util.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"

struct DirectionLight
{
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class PointLight
{
    public:
        PointLight(const VertexBuffer& arrayBuffer);
        PointLight(const PointLight&) = delete;
        PointLight(PointLight&&) = delete;
        ~PointLight() = default;
        PointLight& operator=(const PointLight&) = delete;
        PointLight& operator=(PointLight&&) = delete;

        glm::vec3 position;
        glm::vec3 scale;
        float constant;
        float linear;
        float quadratic;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        void draw(const Shader& shader, const MVP& mvp) const;
    private:
        VertexArray m_vertexArray;
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

struct Lights
{
    DirectionLight directionLight;
    PointLight pointLights[4];
    SpotLight spotLight;
};

#endif