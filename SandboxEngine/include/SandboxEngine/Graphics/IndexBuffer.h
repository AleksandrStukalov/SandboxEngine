#pragma once

namespace SE
{
    enum Type;
    class IndexBuffer
    {
    public:
        IndexBuffer(void* indices, SE::Type type, unsigned int size);
        ~IndexBuffer();
        void bind();

        SE::Type type;
        unsigned int vertexCount;// For keeping count of vertices, when index buffer is used
    private:
        unsigned int id;
    };
}