#pragma once

namespace SE
{
    enum DrawMode
    {
        TRIANGLES,
        LINES,
        POINTS
    };
    enum class PolygonMode
    {
        STANDARD,
        WIREFRAME,
    };

    class VertexArray;
    class IndexBuffer;

    class Renderer
    {
    public:
        Renderer();
        void clear(float r, float g, float b, float a = 1.0f);
        void viewport(int x, int y, int width, int height);
        void setPolygonMode(PolygonMode mode) const;

        void draw(VertexArray& va, DrawMode mode = DrawMode::TRIANGLES);
        void draw(VertexArray& va, IndexBuffer& ib, DrawMode mode = DrawMode::TRIANGLES);
    };
}