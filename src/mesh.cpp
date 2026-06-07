#include "mesh.hpp"
#include "glad.hpp"

Mesh::Mesh(aiMesh* pMesh)
    : m_vertexBuffer{}
    , m_elementBuffer{}
    , m_vertexArray{}
    , m_numIndices{ 0 }
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 textureCoord;
    };

    unsigned int numVertices{ pMesh->mNumVertices };
    Vertex* pVertices{ new Vertex[numVertices] };

    for (unsigned int i{ 0 }; i < numVertices; ++i)
    {
        Vertex vertex;

        vertex.position.x = pMesh->mVertices[i].x;
        vertex.position.y = pMesh->mVertices[i].y;
        vertex.position.z = pMesh->mVertices[i].z;
        vertex.normal.x = pMesh->mNormals[i].x;
        vertex.normal.y = pMesh->mNormals[i].y;
        vertex.normal.z = pMesh->mNormals[i].z;
        vertex.textureCoord.x = pMesh->mTextureCoords[0][i].x;
        vertex.textureCoord.y = pMesh->mTextureCoords[0][i].y;
        pVertices[i] = vertex;
    }

    m_vertexBuffer.bind(GL_ARRAY_BUFFER);
    m_vertexBuffer.data(GL_ARRAY_BUFFER, (sizeof(Vertex) * numVertices), pVertices, GL_STATIC_DRAW);
    m_vertexBuffer.unbind(GL_ARRAY_BUFFER);
    delete[] pVertices;

    struct Face
    {
        glm::uvec3 indices;
    };

    unsigned int numFaces{ pMesh->mNumFaces };
    Face* pFaces{ new Face[numFaces] };

    m_numIndices = 3ul * numFaces;

    for (unsigned int i{ 0 }; i < numFaces; ++i)
    {
        pFaces[i].indices[0] = pMesh->mFaces[i].mIndices[0];
        pFaces[i].indices[1] = pMesh->mFaces[i].mIndices[1];
        pFaces[i].indices[2] = pMesh->mFaces[i].mIndices[2];
    }

    m_elementBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
    m_elementBuffer.data(GL_ELEMENT_ARRAY_BUFFER, (sizeof(Face) * numFaces), pFaces, GL_STATIC_DRAW);
    m_elementBuffer.unbind(GL_ELEMENT_ARRAY_BUFFER);
    delete[] pFaces;

    m_vertexArray.bind();
    m_vertexBuffer.bind(GL_ARRAY_BUFFER);
    m_vertexBuffer.enableVertexAttribArray(0);
    m_vertexBuffer.enableVertexAttribArray(1);
    m_vertexBuffer.enableVertexAttribArray(2);
    m_vertexBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(0));
    m_vertexBuffer.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(12));
    m_vertexBuffer.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(24));
    m_vertexBuffer.unbind(GL_ARRAY_BUFFER);
    m_elementBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
    m_vertexArray.unbind();
    m_elementBuffer.unbind(GL_ELEMENT_ARRAY_BUFFER);
}

void Mesh::draw(const Shader& shader, MVP& mvp, const Material& material) const
{
    shader.use();
    shader.uniformMatrix4fv("uModel", 1, GL_FALSE, &mvp.model[0][0]);
    shader.uniformMatrix4fv("uView", 1, GL_FALSE, &mvp.view[0][0]);
    shader.uniformMatrix4fv("uProjection", 1, GL_FALSE, &mvp.projection[0][0]);
    shader.uniform1i("uDiffuse", 0);
    shader.uniform1i("uSpecular", 1);
    shader.unuse();

    glActiveTexture(GL_TEXTURE0);
    material.diffuse.bind(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    material.specular.bind(GL_TEXTURE_2D);
    shader.use();
    m_vertexArray.bind();
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, reinterpret_cast<const void*>(0));
    m_vertexArray.unbind();
    shader.unuse();
    material.diffuse.bind(GL_TEXTURE_2D);
    material.specular.bind(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
}