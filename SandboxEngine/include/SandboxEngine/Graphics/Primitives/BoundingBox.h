#pragma once

#include "SandboxEngine\Graphics\Mesh.h"

#include <memory>

namespace SE
{
    struct BoundingBox
    {
        BoundingBox(const float scale = 1.0f)
        {
            SE::Vertex vertices[8] {
                // Near
                { {-scale / 2, -scale / 2, scale / 2}, {0, 0} }, // Near Bottom Left    // 0
                { {-scale / 2, scale / 2, scale / 2},  {0, 1} }, // Near Top Left       // 1
                { {scale / 2, scale / 2, scale / 2},   {1, 1} }, // Near Top Right      // 2
                { {scale / 2, -scale / 2, scale / 2},  {1, 0} }, // Near Bottom Right   // 3

                // Far
                { {scale / 2, -scale / 2, -scale / 2}, {0, 0} }, // Far Bottom Left     // 4
                { {scale / 2, scale / 2, -scale / 2},  {0, 1} }, // Far Top Left        // 5
                { {-scale / 2, scale / 2, -scale / 2}, {1, 1} }, // Far Top Right       // 6
                { {-scale / 2, -scale / 2, -scale / 2},{1, 0} }  // Far Bottom Right    // 7
            };
            mesh.reset(new SE::Mesh(vertices, (unsigned int)sizeof(SE::Vertex) * 8, SE::BufferUsage::STATIC_DRAW));
        }
        
        std::unique_ptr<SE::Mesh> mesh;
        unsigned int indices[48] {
            // Near
            0, 1,
            1, 2,
            2, 3,
            3, 0,
            // Far
            4, 5,
            5, 6,
            6, 7,
            7, 4,
            // Left
            7, 6,
            6, 1,
            1, 0,
            0, 7,
            // Right
            3, 2,
            2, 5,
            5, 4,
            4, 3,
            // Bottom
            7, 0,
            0, 3,
            3, 4,
            4, 7,
            // Top
            1, 6,
            6, 5,
            5, 2,
            2, 1
        };
        SE::IndexBuffer ib{ &indices, SE::UNSIGNED_INT, sizeof(unsigned int) * 48, SE::BufferUsage::STATIC_DRAW };
    };
}