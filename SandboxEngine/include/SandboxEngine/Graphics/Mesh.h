#pragma once
#include "SandboxEngine/Maths.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <random>
#include <process.h>
#define RAND rand() / (float)RAND_MAX


namespace SE
{
    struct Vertex
    {
        SE::Vec3f position;
        SE::Vec2f texPos;

        Vertex() {}
        Vertex(SE::Vec3f position, SE::Vec2f texPos)
            : position(position), texPos(texPos) {}
    };
    class Mesh
    {
    public:
        Mesh(Vertex* vertices, const unsigned int vertexCount)
            : vertexCount(vertexCount)
            , vertices(vertices)
            , vb(vertices, sizeof(Vertex) * vertexCount)
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