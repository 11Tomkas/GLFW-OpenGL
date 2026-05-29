#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include "glad.hpp"

Shader::Shader()
    : m_vertex{ glCreateShader(GL_VERTEX_SHADER) }
    , m_fragment{ glCreateShader(GL_FRAGMENT_SHADER) }
    , m_program{ glCreateProgram() }
{
}

Shader::~Shader()
{
    glDeleteShader(m_vertex);
    glDeleteShader(m_fragment);
    glDeleteProgram(m_program);
}

void Shader::compileVertexShader(const char* name) const
{
    std::ifstream file{ name };
    std::ostringstream stream;
    std::string code;
    const char* pCode;

    stream << file.rdbuf();
    code = stream.str();
    pCode = code.c_str();
    glShaderSource(m_vertex, 1, &pCode, nullptr);
    glCompileShader(m_vertex);
    file.close();
}

void Shader::compileFragmentShader(const char* name) const
{
    std::ifstream file{ name };
    std::ostringstream stream;
    std::string code;
    const char* pCode;

    stream << file.rdbuf();
    code = stream.str();
    pCode = code.c_str();
    glShaderSource(m_fragment, 1, &pCode, nullptr);
    glCompileShader(m_fragment);
    file.close();
}

void Shader::linkProgram() const
{
    glAttachShader(m_program, m_vertex);
    glAttachShader(m_program, m_fragment);
    glLinkProgram(m_program);
    glDetachShader(m_program, m_vertex);
    glDetachShader(m_program, m_fragment);
}

void Shader::use() const
{
    glUseProgram(m_program);
}

void Shader::unuse() const
{
    glUseProgram(0);
}

void Shader::uniform1i(const char* name, int v0) const
{
    int uniform{ glGetUniformLocation(m_program, name) };

    glUniform1i(uniform, v0);
}

void Shader::uniform1f(const char* name, float v0) const
{
    int uniform{ glGetUniformLocation(m_program, name) };

    glUniform1f(uniform, v0);
}

void Shader::uniform3f(const char* name, float v0, float v1, float v2) const
{
    int uniform{ glGetUniformLocation(m_program, name) };

    glUniform3f(uniform, v0, v1, v2);
}

void Shader::uniform3fv(const char* name, int count, const float* value) const
{
    int uniform{ glGetUniformLocation(m_program, name) };

    glUniform3fv(uniform, count, value);
}

void Shader::uniformMatrix4fv(const char* name, int count, bool transpose, const float* value) const
{
    int uniform{ glGetUniformLocation(m_program, name) };

    glUniformMatrix4fv(uniform, count, transpose, value);
}