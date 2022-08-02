#pragma once

#include "SandboxEngine/Graphics/Mesh.h"
#include "SandboxEngine/Graphics/Buffers.h"

#include <memory>
#include <vector>


enum VoxelMaterial
{
    AIR = 0,
    SAND,
    GRASS,
    GROUND
};
struct Voxel
{
    static float size;
    uint8_t material;
};
float Voxel::size{ 1.0f };

struct Chunk
{
    SE::Mesh* getMesh(void(*actionsOnMaterial)(Chunk&))
    {
        this->vertexOffset = 0;// Setting offset to zero, so next updateMesh() will rewrite currently present data

        actionsOnMaterial(*this);

        return &this->mesh;
    }

    struct VoxelData{ glm::ivec3 index; glm::vec3 centerPos; };
    struct TextureAtlasData{ glm::ivec2 texRes; glm::ivec2 atlasRes; };
    void addVoxelToMesh(VoxelData voxelData, glm::vec2 texIndex, TextureAtlasData texAtlasData)
    {
        glm::ivec3& index = voxelData.index;
        glm::vec3& centerPos = voxelData.centerPos;
        float edgeLength = Voxel::size;

        if (index.x < this->voxelCount - 1 && voxels[index.x + 1][index.y][index.z].material == VoxelMaterial::AIR)
        {
            this->mesh.vb.add(getRectangle({ centerPos.x + edgeLength / 2, centerPos.y, centerPos.z }, { 1.0f, 0.0f, 0.0f }, texIndex, texAtlasData), sizeof(SE::Vertex) * 4, vertexOffset);
            this->vertexOffset += sizeof(SE::Vertex) * 4;
        }
        if (index.x > 0 && voxels[index.x - 1][index.y][index.z].material == VoxelMaterial::AIR)
        {
            this->mesh.vb.add(getRectangle({ centerPos.x - edgeLength / 2, centerPos.y, centerPos.z }, { -1.0f, 0.0f, 0.0f }, texIndex, texAtlasData), sizeof(SE::Vertex) * 4, vertexOffset);
            this->vertexOffset += sizeof(SE::Vertex) * 4;
        }

        if (index.y < this->voxelCount - 1 && voxels[index.x][index.y + 1][index.z].material == VoxelMaterial::AIR)
        {
            this->mesh.vb.add(getRectangle({ centerPos.x, centerPos.y + edgeLength / 2, centerPos.z }, { 0.0f, 1.0f, 0.0f }, texIndex, texAtlasData), sizeof(SE::Vertex) * 4, vertexOffset);
            this->vertexOffset += sizeof(SE::Vertex) * 4;
        }
        if (index.y > 0 && voxels[index.x][index.y - 1][index.z].material == VoxelMaterial::AIR)
        {
            this->mesh.vb.add(getRectangle({ centerPos.x, centerPos.y - edgeLength / 2, centerPos.z }, { 0.0f, -1.0f, 0.0f }, texIndex, texAtlasData), sizeof(SE::Vertex) * 4, vertexOffset);
            this->vertexOffset += sizeof(SE::Vertex) * 4;
        }

        if (index.z < this->voxelCount - 1 && voxels[index.x][index.y][index.z + 1].material == VoxelMaterial::AIR)
        {
            this->mesh.vb.add(getRectangle({ centerPos.x, centerPos.y, centerPos.z + edgeLength / 2 }, { 0.0f, 0.0f, 1.0f }, texIndex, texAtlasData), sizeof(SE::Vertex) * 4, vertexOffset);
            this->vertexOffset += sizeof(SE::Vertex) * 4;
        }
        if (index.z > 0 && voxels[index.x][index.y][index.z - 1].material == VoxelMaterial::AIR)
        {
            this->mesh.vb.add(getRectangle({ centerPos.x, centerPos.y, centerPos.z - edgeLength / 2 }, { 0.0f, 0.0f, -1.0f }, texIndex, texAtlasData), sizeof(SE::Vertex) * 4, vertexOffset);
            this->vertexOffset += sizeof(SE::Vertex) * 4;
        }
    }


    static const unsigned int voxelCount{ 16 };
    Voxel voxels[voxelCount][voxelCount][voxelCount];
    static const unsigned int vertexCount = 24 * voxelCount * voxelCount * voxelCount;
    static const unsigned int indexCount = 36 * voxelCount * voxelCount * voxelCount;

private:
    SE::Vertex* getRectangle(glm::vec3 centerPos, glm::vec3 normal, glm::vec2 texIndex, TextureAtlasData texAtlasData)
    {
        glm::vec2 atlasRes{ texAtlasData.atlasRes };
        glm::vec2 texRes{ texAtlasData.texRes };
        // NOTE: Conversion from ivec3 to vec3 is done on purpose
        float edgeLength = Voxel::size;
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

    SE::Mesh mesh{nullptr, sizeof(SE::Vertex) * vertexCount, SE::DYNAMIC_DRAW};
    unsigned int vertexOffset{ 0 };
};

class ChunkManager
{
public:
    ChunkManager(void(*setVoxelMaterials)(Chunk& chunk))
    {
        for (int x{}; x < chunkCount; ++x)
            for (int y{}; y < chunkCount; ++y)
                for (int z{}; z < chunkCount; ++z)
                {
                    Chunk& chunk = chunks[x][y][z];
                    setVoxelMaterials(chunk);
                }
    }

    SE::IndexBuffer chunkIB{ getChunkIB() };

    static const unsigned int chunkCount{ 4 };
    Chunk chunks[chunkCount][chunkCount][chunkCount];


private:
    SE::IndexBuffer getChunkIB()
    {
        unsigned int indices[Chunk::indexCount];
        unsigned int offset{ 0 };
        for (unsigned int i{}; i < Chunk::indexCount; i += 36)
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
        return SE::IndexBuffer(indices, SE::UNSIGNED_INT, sizeof(unsigned int) * Chunk::indexCount, SE::STATIC_DRAW);
    }
};