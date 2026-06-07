#include "vertex_buffer.hpp"

#include "glad.hpp"

VertexBuffer::VertexBuffer()
    : m_name{ 0 }
{
    glGenBuffers(1, &m_name);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_name);
}

void VertexBuffer::bind(unsigned int target) const
{
    glBindBuffer(target, m_name);
}

void VertexBuffer::unbind(unsigned int target) const
{
    glBindBuffer(target, 0);
}

void VertexBuffer::data(unsigned int target, long long size, const void* data, unsigned int usage) const
{
    glBufferData(target, size, data, usage);
}

void VertexBuffer::enableVertexAttribArray(unsigned int index)
{
    glEnableVertexAttribArray(index);
}

void VertexBuffer::vertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer) const
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}