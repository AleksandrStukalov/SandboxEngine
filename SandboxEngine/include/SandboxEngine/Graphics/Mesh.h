#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <random>
#include <process.h>
#define RAND rand() / (float)RAND_MAX


namespace SE
{
    struct Vertex
    {
        glm::vec3 vertPos;
        glm::vec2 texPos;

        Vertex() {}
        Vertex(glm::vec3 vertPos, glm::vec2 texPos)
            : vertPos(vertPos), texPos(texPos) {}
    };
    class Mesh
    {
    public:
        inline Mesh(Vertex* vertices, unsigned int size, VBusage usage)
            : vertexCount(size / sizeof(Vertex))
            , vertices(vertices)
            , vb(vertices, size, usage)
        {
            SE::VertexAttribute positions(3, SE::FLOAT);
            SE::VertexAttribute texPos(2, SE::FLOAT);
            SE::VertexBufferLayout layout;
            layout.add(positions);
            layout.add(texPos);
            va.add(vb, layout);
        }

        Vertex* vertices;
        unsigned int vertexCount;

        SE::VertexBuffer vb;
        SE::VertexArray va;
    };
}