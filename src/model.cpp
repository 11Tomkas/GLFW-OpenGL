#include "model.hpp"
#include "assimp.hpp"

Model::Model(const char* fileName)
    : m_numMeshes{ 0 }
    , m_pMeshes{ nullptr }
{
    Assimp::Importer importer;
    const aiScene* pScene{ importer.ReadFile(fileName, aiProcess_Triangulate) };
    aiNode* pRootNode{ pScene->mRootNode };

    m_numMeshes = pRootNode->mNumChildren;
    m_pMeshes = static_cast<Mesh*>(operator new(sizeof(Mesh) * m_numMeshes));

    for (unsigned int i{ 0 }; i < m_numMeshes; ++i)
    {
        aiNode* pChildNode{ pRootNode->mChildren[i] };
        aiMesh* pMesh{ pScene->mMeshes[pChildNode->mMeshes[0]] };

        new (&m_pMeshes[i]) Mesh{ pMesh };
    }
}

Model::~Model()
{
    for (unsigned int i{ 0 }; i < m_numMeshes; ++i)
        m_pMeshes[i].~Mesh();
    operator delete(m_pMeshes);
}

void Model::draw(const Shader& shader, MVP& mvp, const Material& material) const
{
    for (unsigned int i{ 0 }; i < m_numMeshes; ++i)
        m_pMeshes[i].draw(shader, mvp, material);
}