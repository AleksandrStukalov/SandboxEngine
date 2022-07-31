#pragma once

#include "Graphics/Mesh.h"

namespace SE
{
    enum VoxelType
    {
        AIR = 0,
        SAND,
        SOD
    };
    struct Voxel
    {
        VoxelType type;
    };
    struct Chunk
    {


        static const unsigned int size = 16;
        Voxel voxels[size][size][size];

    private:
        inline SE::Vertex* getCube(glm::vec3 pos, float size)
        {
            return new SE::Vertex[24]
            {
                //// VertPos            // TexPos                      // Index
                // Near:
                { { pos.x - size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    0
                { { pos.x - size / 2, pos.y + size / 2, pos.z + size / 2 },    { 0, 1 } },     // Top left     1
                { { pos.x + size / 2, pos.y + size / 2, pos.z + size / 2 },    { 1, 1 } },     // Top right    2
                { { pos.x + size / 2, pos.y - size / 2, pos.z + size / 2 },    { 1, 0 } },     // Down right   3

                // Far
                { { pos.x + size / 2, pos.y - size / 2, pos.z - size / 2 },    { 0, 0 } },     // Down left    4
                { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 0, 1 } },     // Top left     5
                { { pos.x - size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    6
                { { pos.x - size / 2, pos.y - size / 2, pos.z - size / 2 },    { 1, 0 } },     // Down right   7

                // Left
                { { pos.x - size / 2, pos.y - size / 2, pos.z - size / 2 },    { 0, 0 } },     // Down left    8
                { { pos.x - size / 2, pos.y + size / 2, pos.z - size / 2 },    { 0, 1 } },     // Top left     9
                { { pos.x - size / 2, pos.y + size / 2, pos.z + size / 2 },    { 1, 1 } },     // Top right    10
                { { pos.x - size / 2, pos.y - size / 2, pos.z + size / 2 },    { 1, 0 } },     // Down right   11

                // Right
                { { pos.x + size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    12
                { { pos.x + size / 2, pos.y + size / 2, pos.z + size / 2 },    { 0, 1 } },     // Top left     13
                { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    14
                { { pos.x + size / 2, pos.y - size / 2, pos.z - size / 2 },    { 1, 0 } },     // Down right   15

                // Top
                { { pos.x - size / 2, pos.y + size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    16
                { { pos.x - size / 2, pos.y + size / 2, pos.z - size / 2 },    { 0, 1 } },     // Top left     17
                { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    18
                { { pos.x + size / 2, pos.y + size / 2, pos.z + size / 2 },    { 1, 0 } },     // Down right   19

                // Bottom
                { { pos.x - size / 2, pos.y - size / 2, pos.z - size / 2 },    { 0, 0 } },     // Down left    20
                { { pos.x - size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 1 } },     // Top left     21
                { { pos.x + size / 2, pos.y - size / 2, pos.z + size / 2 },    { 1, 1 } },     // Top right    22
                { { pos.x + size / 2, pos.y - size / 2, pos.z - size / 2 },    { 1, 0 } },     // Down right   23
            };
        }
    };
}