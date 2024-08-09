#pragma once

#include <vector>

namespace SE
{
    enum class DrawMode
    {
        TRIANGLES,
        LINES,
        POINTS
    };
    unsigned int getPlatformDrawMode(SE::DrawMode mode);
    enum class PolygonMode
    {
        STANDARD,
        WIREFRAME,
    };

    class VertexArray;
    class IndexBuffer;
    class Shader;
    class Texture;
    class Mesh;
    class Chunk;

    class Renderer
    {
    public:
        Renderer();
        void clear(float r, float g, float b, float a = 1.0f);
        void viewport(int x, int y, int width, int height);
        void setPolygonMode(PolygonMode mode) const;

        void draw(const SE::VertexArray& va, const unsigned int vertexCount, const SE::Shader& shader, DrawMode mode = SE::DrawMode::TRIANGLES);
        void draw(const SE::VertexArray& va, const IndexBuffer& ib, const SE::Shader& shader, DrawMode mode = SE::DrawMode::TRIANGLES);

        unsigned int callCount{};
    };
}