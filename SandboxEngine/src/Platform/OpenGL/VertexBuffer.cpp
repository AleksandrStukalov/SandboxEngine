#include "Graphics/VertexBuffer.h"

#include <glad/glad.h>


SE::VertexBuffer::VertexBuffer(void* vertices, unsigned int size)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

SE::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void SE::VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}