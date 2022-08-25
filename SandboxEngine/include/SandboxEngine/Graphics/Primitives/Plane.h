#pragma once

#include "SandboxEngine/Graphics/Mesh.h"

namespace SE
{
    struct Plane
    {
        SE::Vertex vertices[4] {
            {{-0.5, -0.5, 0.5}, {0.0, 0.0}}, // Bottom left
            {{-0.5, 0.5, 0.5}, {0.0, 1.0}},  // Top left
            {{0.5, 0.5, 0.5}, {1.0, 1.0}},   // Top right
            {{0.5, -0.5, 0.5}, {1.0, 0.0}},  // Bottom right
        };
        SE::Mesh mesh{ vertices, (unsigned int)sizeof(SE::Vertex) * 4, SE::BufferUsage::STATIC_DRAW };

        unsigned int indices[6] {
            0, 1, 2,
            2, 3, 0
        };
        SE::IndexBuffer ib{ &indices, SE::UNSIGNED_INT, sizeof(unsigned int) * 6, SE::BufferUsage::STATIC_DRAW };
    };
}