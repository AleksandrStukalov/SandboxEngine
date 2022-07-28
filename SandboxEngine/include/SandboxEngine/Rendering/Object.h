#pragma once
#include "SandboxEngine/Maths.h"

#include <random>
#include <process.h>
#define RAND rand() / (float)RAND_MAX


namespace SE
{
    struct Vertex
    {
        SE::Vec3f position;
        SE::Vec3f color;
        SE::Vec2f texPos;

        Vertex() {}
        Vertex(SE::Vec3f position, SE::Vec3f color, SE::Vec2f texPos)
            : position(position), color(color), texPos(texPos) {}
        Vertex(SE::Vec3f position, SE::Vec2f texPos)
            : position(position), color(RAND, RAND, RAND), texPos(texPos) {}
    };
    class Object
    {
    public:
        Object(Vertex* vertices, const unsigned int vertexCount, glm::vec3 position = glm::vec3(0.0f), glm::vec3 angle = glm::vec3(0.0f), float size = 1.0f)
            : vertexCount(vertexCount)
            , vertices(vertices)
            , position(position)
            , angle(angle)
            , size(size)
            , vb(vertices, sizeof(Vertex)* vertexCount)// NOTE: Do not shove sizeof(vertices) there! You'll get size of poiter!
        {
            SE::VertexAttribute positions(3, SE::FLOAT);
            SE::VertexAttribute colors(3, SE::FLOAT);
            SE::VertexAttribute texPos(2, SE::FLOAT);
            SE::VertexBufferLayout layout;
            layout.add(positions);
            layout.add(colors);
            layout.add(texPos);
            va.add(vb, layout);
        }

        virtual Vertex* vertexInit() = 0;

        Vertex* vertices;
        unsigned int vertexCount;

        glm::mat4 getModel()
        {
            // Scale:
            glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size, size, size));

            // Rotation:
            glm::mat4 rotation(1.0f);
            rotation = glm::rotate(rotation, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
            rotation = glm::rotate(rotation, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotation = glm::rotate(rotation, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));

            // Translation:
            glm::mat4 translation = glm::translate(glm::mat4(1), position);

            return translation * rotation * scale;
        }

        virtual void onUpdate() = 0;
        virtual void bind()
        {
            va.bind();
        }



        SE::VertexBuffer vb;
        SE::VertexArray va;


        float size;
        glm::vec3 angle;
        glm::vec3 position;
    };
}