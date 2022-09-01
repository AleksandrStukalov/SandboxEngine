#pragma once

#include "Types.h"

#include <vector>

namespace SE
{
    enum Type;
    enum class BufferUsage
    {
        STATIC_DRAW,
        DYNAMIC_DRAW
    };
    unsigned int getPlatformBufferUsage(BufferUsage usage);
    class VertexBuffer
    {
    public:
        VertexBuffer(const void* data, const unsigned int size, BufferUsage usage);
        ~VertexBuffer();
        void bind() const;
        void add(const void* data, const unsigned int size, const unsigned int offset);// NOTE: We can't calculate offset automatically, because it has to be set to zero every frame.

    private:
        unsigned int id;
        BufferUsage usage;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer(const void* indices, SE::Type type, const unsigned int size, BufferUsage usage);
        ~IndexBuffer();
        void bind() const;

        SE::Type type;
        unsigned int indexCount;
    private:
        unsigned int id;
    };

    class VertexAttribute
    {
    public:
        inline VertexAttribute(const unsigned int count, Type type, bool normalized = false)
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

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void add(VertexBuffer& vb, VertexBufferLayout& layout);

    private:
        unsigned int id;
    };
}