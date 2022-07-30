#pragma once

#include "Types.h"

#include <vector>

namespace SE
{
    enum VBusage
    {
        STATIC_DRAW,
        DYNAMIC_DRAW
    };
    unsigned int getPlatformVBusage(VBusage usage);
    class VertexBuffer
    {
    public:
        VertexBuffer(void* vertices, unsigned int size, VBusage usage);
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
        }

        unsigned int stride{ 0 };// NOTE: Must be initialized!

        std::vector<VertexAttribute*> attributes;
    };
}