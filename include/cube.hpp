#ifndef CUBE_HPP
#define CUBE_HPP

#include "util.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "light.hpp"

struct Material
{
    const Texture& diffuse;
    const Texture& specular;
    float shininess;
};

class Cube
{
    public:
        Cube(const VertexBuffer& arrayBuffer);
        Cube(const Cube&) = delete;
        Cube(Cube&&) = delete;
        ~Cube() = default;
        Cube& operator=(const Cube&) = delete;
        Cube& operator=(Cube&&) = delete;

        void setPosition(const glm::vec3& position);
        void setRotation(const glm::vec3& rotation);
        const glm::vec3& position() const;
        const glm::vec3& rotation() const;
        void draw(const Shader& shader, const MVP& mvp, const Material& material, const Lights& lights);
    private:
        VertexArray m_vertexArray;
        glm::vec3 m_position;
        glm::vec3 m_rotation;
};

#endif