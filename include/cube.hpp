#ifndef CUBE_HPP
#define CUBE_HPP

#include "glm.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "texture.hpp"
#include "mvp.hpp"
#include "material.hpp"

struct Light;

class Cube
{
    public:
        Cube();
        Cube(const Cube&) = delete;
        Cube(Cube&&) = delete;
        ~Cube() = default;
        Cube& operator=(const Cube&) = delete;
        Cube& operator=(Cube&&) = delete;

        void setPosition(const glm::vec3& position);
        void setRotation(float angle, const glm::vec3& rotationAxis);
        void setScale(const glm::vec3& scale);
        void draw(const Shader& shader, MVP& mvp, const Material& material, const Light& light);
    protected:
        VertexArray m_vertexArray;
        glm::vec3 m_position;
        float m_angle;
        glm::vec3 m_rotationAxis;
        glm::vec3 m_scale;
};

#endif