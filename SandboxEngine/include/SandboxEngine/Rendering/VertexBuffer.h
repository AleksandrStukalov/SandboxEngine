#pragma once

#include "Types.h"

#include <vector>

namespace SE
{
    class VertexBuffer
    {
    public:
        VertexBuffer(void* vertices, unsigned int size);
        ~VertexBuffer();
        void bind();

    private:
        unsigned int id;
    };

    enum Type;
    class VertexAttribute
    {
    public:
        inline VertexAttribute(unsigned int count, Type type, bool normalized = false)
            : count(count), type(type), normalized(normalized), offset(0) {}
        
        unsigned int count;
        SE::Type type;
        bool normalized;
        unsigned int offset;
    };

    class VertexBufferLayout
    {
    public:
        inline void add(VertexAttribute& attribute)
        {
            attributes.push_back(&attribute);
            attribute.offset = this->stride;
            this->stride += SE::getSizeOfType(attribute.type) * attribute.count;
            vertexCount += attribute.count;
        }

        unsigned int stride{ 0 };// NOTE: Must be initialized!
        unsigned int vertexCount{ 0 };

        std::vector<VertexAttribute*> attributes;
    };
}