#pragma once

#include "SandboxEngine\Graphics.h"

#include "glm/glm.hpp"

#include <memory>

namespace SE
{
    struct BoundingBox
    {
        BoundingBox(const float scale/* = 1.0f*/, glm::vec3 position/* = { 0.0f, 0.0f, 0.0f }*/, glm::vec3 color/* = {0.0f, 0.0f, 0.0f}*/)
        {
            float vertices[6 * 8 * 6]{ // 6 faces * 8 vertices per face * 6 floats per vertex
                // Position                                                                     // Color
                // Near
                -(scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Left    // 0
                -(scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Left       // 1

                -(scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Left       // 1
                (scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Right      // 2

                (scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Right      // 2
                (scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Right   // 3

                (scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Right   // 3
                -(scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Left    // 0

                // Far
                (scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Bottom Left     // 4
                (scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Left        // 5

                (scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Left        // 5
                -(scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Right       // 6

                -(scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Right       // 6
                -(scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b,  // Far Bottom Right    // 7

                -(scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b,  // Far Bottom Right    // 7
                (scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Bottom Left     // 4

                // Left
                -(scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b,  // Far Bottom Right    // 7
                -(scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Right       // 6

                -(scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Right       // 6
                -(scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Left       // 1

                -(scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Left       // 1
                -(scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Left    // 0

                -(scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Left    // 0
                -(scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b,  // Far Bottom Right   // 7

                // Right
                (scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Right   // 3
                 (scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Right      // 2

                 (scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Right      // 2
                 (scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Left        // 5

                 (scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Left        // 5
                 (scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Bottom Left     // 4

                 (scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Bottom Left     // 4
                 (scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Right   // 3

                // Bottom
                -(scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b,  // Far Bottom Right   // 7
                -(scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Left    // 0

                -(scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Left    // 0
                 (scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Right   // 3

                 (scale / 2) + position.x, -(scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Bottom Right   // 3
                 (scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Bottom Left     // 4

                 (scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Bottom Left     // 4
                -(scale / 2) + position.x, -(scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b,  // Far Bottom Right   // 7

                // Top
                -(scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Left       // 1
                -(scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Right       // 6

                -(scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Right       // 6
                 (scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Left        // 5

                 (scale / 2) + position.x,  (scale / 2) + position.y, -(scale / 2) + position.z, color.r, color.g, color.b, // Far Top Left        // 5
                 (scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Right      // 2

                 (scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Right      // 2
                -(scale / 2) + position.x,  (scale / 2) + position.y, (scale / 2) + position.z, color.r, color.g, color.b, // Near Top Left       // 1

            };
            vb.reset(new SE::VertexBuffer(vertices, sizeof(vertices), SE::BufferUsage::STATIC_DRAW));
            
            SE::VertexAttribute positionAttribute(3, SE::FLOAT);
            SE::VertexAttribute colorAttribute(3, SE::FLOAT);
            SE::VertexBufferLayout layout;
            layout.add(positionAttribute);
            layout.add(colorAttribute);
            va->add(*vb.get(), layout, 48);

        }
        std::unique_ptr<SE::VertexBuffer> vb;
        std::unique_ptr<SE::VertexArray> va{ new SE::VertexArray() };
        //unsigned int indices[48]{
        //    // Near
        //    0, 1,
        //    1, 2,
        //    2, 3,
        //    3, 0,
        //    // Far
        //    4, 5,
        //    5, 6,
        //    6, 7,
        //    7, 4,
        //    // Left
        //    7, 6,
        //    6, 1,
        //    1, 0,
        //    0, 7,
        //    // Right
        //    3, 2,
        //    2, 5,
        //    5, 4,
        //    4, 3,
        //    // Bottom
        //    7, 0,
        //    0, 3,
        //    3, 4,
        //    4, 7,
        //    // Top
        //    1, 6,
        //    6, 5,
        //    5, 2,
        //    2, 1
        //};
        //std::unique_ptr<SE::IndexBuffer> ib{ new SE::IndexBuffer{ &indices, SE::UNSIGNED_INT, sizeof(unsigned int) * 48, SE::BufferUsage::STATIC_DRAW } };
    };
}