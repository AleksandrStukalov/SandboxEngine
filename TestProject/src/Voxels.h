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
    uint8_t type;
};
struct ChunkBase
{
    // For providing voxel type to every voxel depending on its index(position) in chunk
    virtual void setVoxelType(Voxel& voxel, glm::vec3 index) = 0;
    // Sets type for every voxel in chunk
    void generate()
    {
        // Setting voxel types:
        for (int x{}; x < voxelCount; ++x)
            for (int z{ 0 }; z < voxelCount; ++z)
                for (int y{ 0 }; y < voxelCount; ++y)
                {
                    Voxel& voxel = voxels[x][y][z];
                    setVoxelType(voxel, { x, y, z });
                }
    }
    // For providing actions, which will be executed for every voxel tyoe
    virtual void setActiosOnType(Voxel& voxel, glm::vec3 index) = 0;

    SE::Mesh* getMesh()
    {
        updateMesh();
        return &this->mesh;
    }

    // Adds cube faces to the vertex buffer if they are not blocked by some other block
    void addCube(glm::vec3 centerPos, float edgeLength, glm::vec2 texIndex, glm::vec2 texRes, glm::vec2 atlasRes)
    {
        int x = centerPos.x, y = centerPos.y, z = centerPos.z;
        if (x == this->voxelCount - 1 || voxels[x + 1][y][z].type == VoxelType::AIR)
        {
            this->mesh.vb.add(getQuad({ x + edgeLength / 2, y, z }, edgeLength, { 1.0f, 0.0f, 0.0f }, texIndex, texRes, atlasRes), sizeof(SE::Vertex) * 4, offset);
            this->offset += sizeof(SE::Vertex) * 4;
        }
        if (x == 0 || voxels[x - 1][y][z].type == VoxelType::AIR)
        {
            this->mesh.vb.add(getQuad({ x - edgeLength / 2, y, z }, edgeLength, { -1.0f, 0.0f, 0.0f }, texIndex, texRes, atlasRes), sizeof(SE::Vertex) * 4, offset);
            this->offset += sizeof(SE::Vertex) * 4;
        }
        if (y == this->voxelCount - 1 || voxels[x][y + 1][z].type == VoxelType::AIR)
        {
            this->mesh.vb.add(getQuad({ x, y + edgeLength / 2, z }, edgeLength, { 0.0f, 1.0f, 0.0f }, texIndex, texRes, atlasRes), sizeof(SE::Vertex) * 4, offset);
            this->offset += sizeof(SE::Vertex) * 4;
        }
        if (y == 0 || voxels[x][y - 1][z].type == VoxelType::AIR)
        {
            this->mesh.vb.add(getQuad({ x, y - edgeLength / 2, z }, edgeLength, { 0.0f, -1.0f, 0.0f }, texIndex, texRes, atlasRes), sizeof(SE::Vertex) * 4, offset);
            this->offset += sizeof(SE::Vertex) * 4;
        }
        if (z == this->voxelCount - 1 || voxels[x][y][z + 1].type == VoxelType::AIR)
        {
            this->mesh.vb.add(getQuad({ x, y, z + edgeLength / 2 }, edgeLength, { 0.0f, 0.0f, 1.0f }, texIndex, texRes, atlasRes), sizeof(SE::Vertex) * 4, offset);
            this->offset += sizeof(SE::Vertex) * 4;
        }
        if (z == 0 || voxels[x][y][z - 1].type == VoxelType::AIR)
        {
            this->mesh.vb.add(getQuad({ x, y, z - edgeLength / 2 }, edgeLength, { 0.0f, 0.0f, -1.0f }, texIndex, texRes, atlasRes), sizeof(SE::Vertex) * 4, offset);
            this->offset += sizeof(SE::Vertex) * 4;
        }
    }

    float cubeSize{ 1.0f };
    static const unsigned int voxelCount = 36;
    static const unsigned int vertexCount = 24 * voxelCount * voxelCount * voxelCount;
    static const unsigned int indexCount = 36 * voxelCount * voxelCount * voxelCount;

    Voxel voxels[voxelCount][voxelCount][voxelCount];
    std::unique_ptr<SE::IndexBuffer> ib{ new SE::IndexBuffer { *getIB() } };

private:
    // Returns textured rectangle vertides, which position is set according the normal(direction) vector of the rectangle. Texture is designed to be takem from atlas.
    SE::Vertex* getQuad(glm::vec3 centerPos, float edgeLength, glm::vec3 normal, glm::vec2 texIndex, glm::vec2 texRes, glm::vec2 atlasRes)
    {
        glm::vec2 texPos[4]
        {
            {(texIndex.x * texRes.x) / atlasRes.x, (texIndex.y * texRes.y) / atlasRes.y},
            {(texIndex.x * texRes.x) / atlasRes.x, ((texIndex.y + 1) * texRes.y) / atlasRes.y},
            {((texIndex.x + 1) * texRes.x) / atlasRes.x, ((texIndex.y + 1) * texRes.y) / atlasRes.y},
            {((texIndex.x + 1) * texRes.x) / atlasRes.x, (texIndex.y * texRes.y) / atlasRes.y}
        };

        if (normal == glm::vec3(1.0f, 0.0f, 0.0f))// +X
        {
            return new SE::Vertex[4]
            {
                { { centerPos.x, centerPos.y - edgeLength / 2, centerPos.z + edgeLength / 2 },    texPos[0] },
                { { centerPos.x, centerPos.y + edgeLength / 2, centerPos.z + edgeLength / 2 },    texPos[1] },
                { { centerPos.x, centerPos.y + edgeLength / 2, centerPos.z - edgeLength / 2 },    texPos[2] },
                { { centerPos.x, centerPos.y - edgeLength / 2, centerPos.z - edgeLength / 2 },    texPos[3] },
            };
        }
        else if (normal == glm::vec3(-1.0f, 0.0f, 0.0f))// -X
        {
            return new SE::Vertex[4]
            {
                { { centerPos.x, centerPos.y - edgeLength / 2, centerPos.z - edgeLength / 2 },    texPos[0] },
                { { centerPos.x, centerPos.y + edgeLength / 2, centerPos.z - edgeLength / 2 },    texPos[1] },
                { { centerPos.x, centerPos.y + edgeLength / 2, centerPos.z + edgeLength / 2 },    texPos[2] },
                { { centerPos.x, centerPos.y - edgeLength / 2, centerPos.z + edgeLength / 2 },    texPos[3] },
            };
        }
        else if (normal == glm::vec3(0.0f, 1.0f, 0.0f))// +Y
        {
            return new SE::Vertex[4]
            {
                { { centerPos.x - edgeLength / 2, centerPos.y, centerPos.z + edgeLength / 2 },    texPos[0] },
                { { centerPos.x - edgeLength / 2, centerPos.y, centerPos.z - edgeLength / 2 },    texPos[1] },
                { { centerPos.x + edgeLength / 2, centerPos.y, centerPos.z - edgeLength / 2 },    texPos[2] },
                { { centerPos.x + edgeLength / 2, centerPos.y, centerPos.z + edgeLength / 2 },    texPos[3] },
            };
        }
        else if (normal == glm::vec3(0.0f, -1.0f, 0.0f))// -Y
        {
            return new SE::Vertex[4]
            {
                { { centerPos.x - edgeLength / 2, centerPos.y, centerPos.z - edgeLength / 2 },    texPos[0] },
                { { centerPos.x - edgeLength / 2, centerPos.y, centerPos.z + edgeLength / 2 },    texPos[1] },
                { { centerPos.x + edgeLength / 2, centerPos.y, centerPos.z + edgeLength / 2 },    texPos[2] },
                { { centerPos.x + edgeLength / 2, centerPos.y, centerPos.z - edgeLength / 2 },    texPos[3] },
            };
        }
        else if (normal == glm::vec3(0.0f, 0.0f, 1.0f))// +Z
        {
            return new SE::Vertex[4]
            {
                //// VertPos                                                                                 // TexPos
                { { centerPos.x - edgeLength / 2, centerPos.y - edgeLength / 2, centerPos.z },    texPos[0] },
                { { centerPos.x - edgeLength / 2, centerPos.y + edgeLength / 2, centerPos.z },    texPos[1] },
                { { centerPos.x + edgeLength / 2, centerPos.y + edgeLength / 2, centerPos.z },    texPos[2] },
                { { centerPos.x + edgeLength / 2, centerPos.y - edgeLength / 2, centerPos.z },    texPos[3] },
            };
        }
        else if (normal == glm::vec3(0.0f, 0.0f, -1.0f))// -Z
        {
            return new SE::Vertex[4]
            {
                { { centerPos.x + edgeLength / 2, centerPos.y - edgeLength / 2, centerPos.z },    texPos[0] },
                { { centerPos.x + edgeLength / 2, centerPos.y + edgeLength / 2, centerPos.z },    texPos[1] },
                { { centerPos.x - edgeLength / 2, centerPos.y + edgeLength / 2, centerPos.z },    texPos[2] },
                { { centerPos.x - edgeLength / 2, centerPos.y - edgeLength / 2, centerPos.z },    texPos[3] },
            };
        }
        else
        {
            SE::Log::error({ "Invalid normal vector" });
            return nullptr;
        }
       
    }
    // Returns index buffer, which describes all the voxel vertices in chunk
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
    // Executes actions on each voxel type (generates or does not generate mesh for a specific type)
    void updateMesh()
    {
        for (int x{}; x < voxelCount; ++x)
            for (int z{ 0 }; z < voxelCount; ++z)
                for (int y{ 0 }; y < voxelCount; ++y)
                {
                    Voxel& voxel = voxels[x][y][z];
                    setActiosOnType(voxel, { x, y, z });
                }
        this->offset = 0;// Setting offset to zero, so next updateMesh() will rewrite currently present data
    }

    SE::Mesh mesh{nullptr, sizeof(SE::Vertex) * vertexCount, SE::DYNAMIC_DRAW};
    unsigned int offset{ 0 };
};
