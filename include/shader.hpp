#ifndef SHADER_HPP
#define SHADER_HPP

class Shader
{
    public:
        Shader();
        Shader(const Shader&) = delete;
        Shader(Shader&&) = delete;
        ~Shader();
        Shader& operator=(const Shader&) = delete;
        Shader& operator=(Shader&&) = delete;

        void compileVertexShader(const char* name) const;
        void compileFragmentShader(const char* name) const;
        void linkProgram() const;
        void use() const;
        void unuse() const;
        void uniform1i(const char* name, int v0) const;
        void uniform1f(const char* name, float v0) const;
        void uniform3f(const char* name, float v0, float v1, float v2) const;
        void uniform3fv(const char* name, int count, const float* value) const;
        void uniformMatrix4fv(const char* name, int count, bool transpose, const float* value) const;
    private:
        unsigned int m_vertex;
        unsigned int m_fragment;
        unsigned int m_program;
};

#endif