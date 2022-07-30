#include "Graphics/VertexBuffer.h"

#include <glad/glad.h>


unsigned int SE::getPlatformVBusage(VBusage usage)
{
    switch (usage)
    {
    case SE::STATIC_DRAW:   return GL_STATIC_DRAW;
    case SE::DYNAMIC_DRAW:  return GL_DYNAMIC_DRAW;
    default:                SE::Log::error({ "Unsupported SE vertex buffer usage: ", (const char*) usage }); return -1;
    }
}
SE::VertexBuffer::VertexBuffer(void* vertices, unsigned int size, VBusage usage)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, getPlatformVBusage(usage));
}

SE::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void SE::VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

