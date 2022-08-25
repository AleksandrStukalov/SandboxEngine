#pragma once

#include "SandboxEngine\Graphics\Mesh.h"

namespace SE
{
    struct Cube
    {
        SE::Vertex vertices[24]{
            // Near
            {{-0.5, -0.5, 0.5}, {0, 0}}, // Near Bottom Left
            {{-0.5, 0.5, 0.5},  {0, 1}}, // Near Top Left
            {{0.5, 0.5, 0.5},   {1, 1}}, // Near Top Right
            {{0.5, -0.5, 0.5},  {1, 0}}, // Near Bottom Right

            // Far
            {{0.5, -0.5, -0.5}, {0, 0}}, // Far Bottom Left
            {{0.5, 0.5, -0.5},  {0, 1}}, // Far Top Left
            {{-0.5, 0.5, -0.5}, {1, 1}}, // Far Top Right
            {{-0.5, -0.5, -0.5},{1, 0}}, // Far Bottom Right

            // Left
            {{-0.5, -0.5, -0.5}, {0, 0}}, // Far Bottom Left
            {{-0.5, 0.5, -0.5},  {0, 1}}, // Far Top Left
            {{-0.5, 0.5, 0.5},   {1, 1}},  // Near Top Left
            {{-0.5, -0.5, 0.5},  {1, 0}}, // Near Bottom Left

            // Right
            {{0.5, -0.5, 0.5},  {0, 0}},   // Near Bottom Right
            {{0.5, 0.5, 0.5},   {0, 1}},   // Near Top Right
            {{0.5, 0.5, -0.5},  {1, 1}},  // Far Top Right
            {{0.5, -0.5, -0.5}, {1, 0}},  // Far Bottom Right

            // Bottom
            {{0.5, -0.5, -0.5},  {0, 0}}, // Far Bottom Left
            {{-0.5, -0.5, 0.5},  {0, 1}}, // Near Bottom Left
            {{0.5, -0.5, 0.5},   {1, 1}}, // Near Bottom Right
            {{-0.5, -0.5, -0.5}, {1, 0}}, // Far Bottom Right

            // Top
            {{-0.5, 0.5, 0.5},  {0, 0}},    // Near Top Left
            {{-0.5, 0.5, -0.5}, {0, 1}},    // Far Top Left
            {{0.5, 0.5, -0.5},  {1, 1}},    // Far Top Right
            {{0.5, 0.5, 0.5},   {1, 0}},    // Near Top Right
        };
        SE::Mesh mesh{ vertices, (unsigned int)sizeof(SE::Vertex) * 24, SE::BufferUsage::STATIC_DRAW };
        unsigned int indices[36]{
            // Near
            0, 1, 2,
            2, 3, 0,
            // Far
            4, 5, 6,
            6, 7, 4,
            // Left
            8, 9, 10,
            10, 11, 8,
            // Right
            12, 13, 14,
            14, 15, 12,
            // Bottom
            16, 17, 18,
            18, 19, 16,
            // Top
            20, 21, 22,
            22, 23, 20
        };
        SE::IndexBuffer ib{ &indices, SE::UNSIGNED_INT, sizeof(unsigned int) * 36, SE::BufferUsage::STATIC_DRAW };
    };
}