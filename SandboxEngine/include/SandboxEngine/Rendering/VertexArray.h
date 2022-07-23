#pragma once

namespace SE
{
    class VertexBuffer;
    class VertexBufferLayout;
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
        void bind();
        void add(VertexBuffer& vb, VertexBufferLayout& layout);

        unsigned int vertexCount;// For keeping count of vertices, when index buffer is not used
    private:
        unsigned int id;
    };
}