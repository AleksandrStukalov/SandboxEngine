#include "Rendering.h"

#include "glad/glad.h"

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
    vertexCount = layout.vertexCount;

    this->bind();
    vb.bind();

    for (int i{}; i < layout.attributes.size(); ++i)
    {
        auto& attribute = *layout.attributes[i];
        glVertexAttribPointer(i, attribute.count, SE::getPlatformType(attribute.type), attribute.normalized, layout.stride, (void*)attribute.offset);
        glEnableVertexAttribArray(i);
    }
}