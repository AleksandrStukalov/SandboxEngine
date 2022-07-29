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

    class Renderer
    {
    public:
        Renderer();
        void clear(float r, float g, float b, float a = 1.0f);
        void viewport(int x, int y, int width, int height);
        void setPolygonMode(PolygonMode mode) const;
        unsigned int getPlatformDrawMode(SE::DrawMode mode);

        void draw(Mesh* mesh, Shader* shader, Texture* texture, DrawMode mode = DrawMode::TRIANGLES);

    };
}