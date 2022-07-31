#include "Graphics/Buffers.h"

#include <glad/glad.h>


unsigned int SE::getPlatformBufferUsage(SE::BufferUsage usage)
{
    switch (usage)
    {
    case SE::STATIC_DRAW:   return GL_STATIC_DRAW;
    case SE::DYNAMIC_DRAW:  return GL_DYNAMIC_DRAW;
    default:                SE::Log::error({ "Unsupported SE buffer usage: ", (const char*)usage }); return -1;
    }
}

// Vertex buffer:
SE::VertexBuffer::VertexBuffer(void* vertices, unsigned int size, SE::BufferUsage usage)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, getPlatformBufferUsage(usage));
}

SE::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void SE::VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

// Index buffer:
SE::IndexBuffer::IndexBuffer(void* indices, SE::Type type, unsigned int size, BufferUsage usage)
    : type(type)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, getPlatformBufferUsage(usage));

    indexCount = size / SE::getSizeOfType(type);
}

SE::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &id);
}

void SE::IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

// Vertex array:
SE::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
}

SE::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}

void SE::VertexArray::bind()
{
    glBindVertexArray(id);
}

void SE::VertexArray::add(VertexBuffer& vb, VertexBufferLayout& layout)
{
    this->bind();
    vb.bind();

    for (int i{}; i < layout.attributes.size(); ++i)
    {
        auto& attribute = *layout.attributes[i];
        glVertexAttribPointer(i, attribute.count, SE::getPlatformType(attribute.type), attribute.normalized, layout.stride, (void*)attribute.offset);
        glEnableVertexAttribArray(i);
    }
}