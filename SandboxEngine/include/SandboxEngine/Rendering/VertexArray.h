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

        unsigned int vertexCount;
    private:
        unsigned int id;
    };
}