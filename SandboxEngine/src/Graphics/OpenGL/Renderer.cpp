#include "Graphics.h"
#include "OpenGLContext.h"

#include <glad/glad.h>

SE::Renderer::Renderer()
{
    // Initializing OpenGL context:
    OpenGLContext::init();
    // NOTE: OpenGL context gets initialized independantly for each window.
}

void SE::Renderer::viewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void SE::Renderer::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int SE::getPlatformDrawMode(SE::DrawMode mode)
{
    switch (mode)
    {
    case SE::DrawMode::TRIANGLES:   return GL_TRIANGLES;
    case SE::DrawMode::LINES:       return GL_LINES;
    case SE::DrawMode::POINTS:      return GL_POINTS;
    default:                        SE::Log::error({ "Unsupported drawing mode" }); return -1;
    }
}

void SE::Renderer::setPolygonMode(PolygonMode mode) const
{
    switch (mode)
    {
        case SE::PolygonMode::STANDARD:     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
        case SE::PolygonMode::WIREFRAME:    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        default:                            SE::Log::error({ "Unsupported mode" });
    }
}

void SE::Renderer::draw(const SE::VertexArray& va, const unsigned int vertexCount, const SE::Shader& shader, DrawMode mode)
{
    shader.bind();
    va.bind();
    glDrawArrays(getPlatformDrawMode(mode), 0, vertexCount);
    ++callCount;
}

void SE::Renderer::draw(const SE::VertexArray& va, const IndexBuffer& ib, const SE::Shader& shader, DrawMode mode)
{
    shader.bind();
    va.bind();
    ib.bind();
    glDrawElements(getPlatformDrawMode(mode), ib.indexCount, getPlatformType(ib.type), 0);
    ++callCount;
}

