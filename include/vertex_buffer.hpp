#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

class VertexBuffer
{
    public:
        VertexBuffer();
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer(VertexBuffer&&) = delete;
        ~VertexBuffer();
        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer& operator=(VertexBuffer&&) = delete;

        void bind(unsigned int target) const;
        void unbind(unsigned int target) const;
        void data(unsigned int target, long long size, const void* data, unsigned int usage) const;
        void enableVertexAttribArray(unsigned int index);
        void vertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer) const;
    private:
        unsigned int m_name;
};

#endif