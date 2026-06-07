#ifndef MODEL_HPP
#define MODEL_HPP

#include "shader.hpp"
#include "mvp.hpp"
#include "material.hpp"
#include "mesh.hpp"

class Model
{
    public:
        Model(const char* fileName);
        Model(const Model&) = delete;
        Model(Model&&) = delete;
        ~Model();

        void draw(const Shader& shader, MVP& mvp, const Material& material) const;
    private:
        unsigned int m_numMeshes;
        Mesh* m_pMeshes;
};

#endif