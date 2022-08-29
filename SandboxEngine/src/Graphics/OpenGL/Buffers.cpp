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
SE::VertexBuffer::VertexBuffer(const void* data, const unsigned int size, SE::BufferUsage usage)
    : usage(usage)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, getPlatformBufferUsage(usage));
}

SE::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void SE::VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void SE::VertexBuffer::add(const void* data, const unsigned int size, const unsigned int offset)
{
    if (usage != SE::DYNAMIC_DRAW) SE::Log::error({ "Can't add data to static buffer" });
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

// Index buffer:
SE::IndexBuffer::IndexBuffer(const void* indices, SE::Type type, const unsigned int size, BufferUsage usage)
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

void SE::IndexBuffer::bind() const
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

void SE::VertexArray::bind() const
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
