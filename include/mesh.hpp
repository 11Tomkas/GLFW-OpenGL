#ifndef MESH_HPP
#define MESH_HPP

#include "assimp.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "mvp.hpp"
#include "material.hpp"

class Mesh
{
    public:
        Mesh(aiMesh* pMesh);
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&&) = delete;
        ~Mesh() = default;
        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&) = delete;

        void draw(const Shader& shader, MVP& mvp, const Material& material) const;
    private:
        VertexBuffer m_vertexBuffer;
        VertexBuffer m_elementBuffer;
        VertexArray m_vertexArray;
        unsigned int m_numIndices;
};

#endif