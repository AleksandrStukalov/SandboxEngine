#pragma once

namespace SE
{
    class VertexBuffer
    {
    public:
        VertexBuffer(void* vertices, unsigned int size);
        ~VertexBuffer();
        void bind();
        
        unsigned int id;
    };
}