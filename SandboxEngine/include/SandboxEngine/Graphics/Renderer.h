#pragma once

#include <vector>

namespace SE
{
    enum DrawMode
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

        void SE::Renderer::draw(Mesh& mesh, Shader& shader, Texture& texture, DrawMode mode = SE::DrawMode::TRIANGLES);
        void SE::Renderer::draw(Mesh& mesh, IndexBuffer& ib, Shader& shader, Texture& texture, DrawMode mode = SE::DrawMode::TRIANGLES);
    };
}