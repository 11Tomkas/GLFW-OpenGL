#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

class VertexArray
{
    public:
        VertexArray();
        VertexArray(const VertexArray&) = delete;
        VertexArray(VertexArray&&) = delete;
        ~VertexArray();
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray& operator=(VertexArray&&) = delete;

        void bind() const;
        void unbind() const;
    private:
        unsigned int m_name;
};

#endif