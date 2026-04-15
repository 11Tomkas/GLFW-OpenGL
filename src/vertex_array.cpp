#include "vertex_array.hpp"

#include "glad\gl.h"

VertexArray::VertexArray()
    : m_name{ 0 }
{
    glGenVertexArrays(1, &m_name);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_name);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_name);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}