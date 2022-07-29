#include "Graphics/IndexBuffer.h"

#include <glad/glad.h>

SE::IndexBuffer::IndexBuffer(void* indices, SE::Type type, unsigned int size)
    : type(type)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    vertexCount = size / SE::getSizeOfType(type);
}

SE::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &id);
}

void SE::IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}
