#pragma once

#include "SandboxEngine/Graphics/Mesh.h"
#include "SandboxEngine/Graphics/Buffers.h"

#include <memory>
#include <vector>


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
    virtual void setTypes() = 0;

    SE::Mesh* getMesh()
    {
        setTypes();
        // Updating cubes:
        unsigned int offset{ 0 };
        unsigned int size = sizeof(SE::Vertex) * 24;
        for (int x{}; x < count; ++x)
            for (int y{}; y < count; ++y)
                for (int z{}; z < count; ++z)
                {
                    Voxel& voxel = voxels[x][y][z];
                    if (voxel.type == VoxelType::AIR) continue; // Not rendering air
                    // Updating meshes:
                    std::unique_ptr<SE::Vertex> vertices(getCube(glm::vec3(x, y, z), 1.0f));
                    this->mesh.vb.add(vertices.get(), size, offset);
                    offset += size;
                }
        return &this->mesh;
    }

    static const unsigned int count = 16;
    static const unsigned int vertexCount = 24 * count * count * count;
    static const unsigned int indexCount = 36 * count * count * count;

    Voxel voxels[count][count][count];
    SE::IndexBuffer ib{ *getIB() };

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
    SE::IndexBuffer* getIB()
        {
            unsigned int* indices = new unsigned int[this->indexCount];
            unsigned int offset{ 0 };
            for (unsigned int i{}; i < this->indexCount; i += 36)
            {
                // Near:
                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                // Far:
                indices[i + 6] = offset + 4;
                indices[i + 7] = offset + 5;
                indices[i + 8] = offset + 6;

                indices[i + 9] = offset + 6;
                indices[i + 10] = offset + 7;
                indices[i + 11] = offset + 4;

                // Left:
                indices[i + 12] = offset + 8;
                indices[i + 13] = offset + 9;
                indices[i + 14] = offset + 10;

                indices[i + 15] = offset + 10;
                indices[i + 16] = offset + 11;
                indices[i + 17] = offset + 8;

                // Right:
                indices[i + 18] = offset + 12;
                indices[i + 19] = offset + 13;
                indices[i + 20] = offset + 14;

                indices[i + 21] = offset + 14;
                indices[i + 22] = offset + 15;
                indices[i + 23] = offset + 12;

                // Top:
                indices[i + 24] = offset + 16;
                indices[i + 25] = offset + 17;
                indices[i + 26] = offset + 18;

                indices[i + 27] = offset + 18;
                indices[i + 28] = offset + 19;
                indices[i + 29] = offset + 16;

                // Bottom:
                indices[i + 30] = offset + 20;
                indices[i + 31] = offset + 21;
                indices[i + 32] = offset + 22;

                indices[i + 33] = offset + 22;
                indices[i + 34] = offset + 23;
                indices[i + 35] = offset + 20;

                offset += 24;
            }
            SE::IndexBuffer* ib = new SE::IndexBuffer(indices, SE::UNSIGNED_INT, sizeof(unsigned int) * indexCount, SE::STATIC_DRAW);
            delete[] indices;
            return ib;
        }
    SE::Mesh mesh{nullptr, sizeof(SE::Vertex) * vertexCount, SE::DYNAMIC_DRAW};
};
