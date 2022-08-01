#pragma once

#include "SandboxEngine/Graphics/Mesh.h"
#include "SandboxEngine/Graphics/Buffers.h"

#include <memory>
#include <vector>


enum VoxelType
{
    AIR = 0,
    SAND,
    GRASS,
    GROUND
};
struct Voxel
{
    VoxelType type;
};
struct ChunkBase
{
    virtual void processVoxel(Voxel& voxel, glm::vec3 centerPos) = 0;

    SE::Mesh* getMesh()
    {
        // Updating cubes:
        for (int x{}; x < count; ++x)
            for (int y{}; y < count; ++y)
                for (int z{}; z < count; ++z)
                {
                    Voxel& voxel = voxels[x][y][z];
                    processVoxel(voxel, { x, y, z });
                }
        this->offset = 0;
        return &this->mesh;
    }

    void addCube(glm::vec3 centerPos, float cubeSize, glm::vec2 texIndex, glm::vec2 texRes, glm::vec2 atlasRes)
    {
        std::unique_ptr<SE::Vertex> vertices(getCube(centerPos, cubeSize, texIndex, texRes, atlasRes));
        this->mesh.vb.add(vertices.get(), sizeof(SE::Vertex) * 24, offset);
        this->offset += sizeof(SE::Vertex) * 24;
    }

    static const unsigned int count = 16;
    static const unsigned int vertexCount = 24 * count * count * count;
    static const unsigned int indexCount = 36 * count * count * count;

    Voxel voxels[count][count][count];
    std::unique_ptr<SE::IndexBuffer> ib{ new SE::IndexBuffer { *getIB() } };

private:
    inline SE::Vertex* getCube(glm::vec3 centerPos, float cubeSize, glm::vec2 texIndex, glm::vec2 texRes, glm::vec2 atlasRes)
    {
        glm::vec2 texPos[4]
        {
            {(texIndex.x * texRes.x) / atlasRes.x, (texIndex.y * texRes.y) / atlasRes.y},
            {(texIndex.x * texRes.x) / atlasRes.x, ((texIndex.y + 1) * texRes.y) / atlasRes.y},
            {((texIndex.x + 1) * texRes.x) / atlasRes.x, ((texIndex.y + 1) * texRes.y) / atlasRes.y},
            {((texIndex.x + 1) * texRes.x) / atlasRes.x, (texIndex.y * texRes.y) / atlasRes.y}
        };

        return new SE::Vertex[24]
        {
                //// VertPos                                                                                 // TexPos                          // Index
                // Near:
                { { centerPos.x - cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[0] },     // Bottom left    0
                { { centerPos.x - cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[1] },     // Top left       1
                { { centerPos.x + cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[2] },     // Top right      2
                { { centerPos.x + cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[3] },     // Bottom right   3

                // Far
                { { centerPos.x + cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[0] },     // Bottom left    4
                { { centerPos.x + cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[1] },     // Top left       5
                { { centerPos.x - cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[2] },     // Top right      6
                { { centerPos.x - cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[3] },     // Bottom right   7

                // Left
                { { centerPos.x - cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[0] },     // Bottom left    8
                { { centerPos.x - cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[1] },     // Top left       9
                { { centerPos.x - cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[2] },     // Top right      10
                { { centerPos.x - cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[3] },     // Bottom right   11

                // Right
                { { centerPos.x + cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[0] },     // Bottom left    12
                { { centerPos.x + cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[1] },     // Top left       13
                { { centerPos.x + cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[2] },     // Top right      14
                { { centerPos.x + cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[3] },     // Bottom right   15

                // Top
                { { centerPos.x - cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[0] },     // Bottom left    16
                { { centerPos.x - cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[1] },     // Top left       17
                { { centerPos.x + cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[2] },     // Top right      18
                { { centerPos.x + cubeSize / 2, centerPos.y + cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[3] },     // Bottom right   19

                // Bottom
                { { centerPos.x - cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[0] },     // Bottom left    20
                { { centerPos.x - cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[1] },     // Top left       21
                { { centerPos.x + cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z + cubeSize / 2 },    texPos[2] },     // Top right      22
                { { centerPos.x + cubeSize / 2, centerPos.y - cubeSize / 2, centerPos.z - cubeSize / 2 },    texPos[3] },     // Bottom right   23
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

    unsigned int offset{ 0 };
};
