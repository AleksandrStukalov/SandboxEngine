#include "SandboxEngine.h"

#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <memory>


class App : public SE::Application
{
public:

    App()
        : Application("App", 800, 600)
    {
        float vertices[]
        {
            -0.5f, -0.5f, 0.0f,   // Bottom left
             -0.5f, 0.5f, 0.0f,   // Top left
             0.5f, 0.5f, 0.0f,    // Top right
             0.5f, -0.5f, 0.0f    // Bottom right
        };

        unsigned int indices[]
        { 
            0,1,2,
            2,3,0 
        };


        vb.reset(new SE::VertexBuffer(vertices, sizeof(vertices)));
        ib.reset(new SE::IndexBuffer(indices, SE::UNSIGNED_INT, sizeof(indices)));
        va.reset(new SE::VertexArray());

        SE::VertexAttribute positions(3, SE::FLOAT);
        SE::VertexBufferLayout layout;
        layout.add(positions);

        va.get()->add(*vb.get(), layout);

    }

    ~App()
    {
       
    }

    void onUpdate() override
    {
        if (events.isKey(SE::Key::A, SE::Action::PRESSED))
        {
            SE::Log::info({ "A pressed" });
        }
        if (events.isMouseButton(SE::MouseButton::LEFT, SE::Action::PRESSED))
        {
            SE::Log::info({ "LMB" });
        }

        renderer.clear(0.2f, 0.2f, 0.2f);

        renderer.draw(*va.get(), *ib.get());

    }

    void processMouseMovement(float xoffset, float yoffset) override
    {
        std::stringstream message; 
        message << "xoffset: "; 
        message << xoffset;
        message << "\t yoffset: ";
        message << yoffset;
        SE::Log::info({ message.str() });
    }

    std::unique_ptr<SE::VertexBuffer> vb;
    std::unique_ptr<SE::VertexArray> va;
    std::unique_ptr<SE::IndexBuffer> ib;
};

int main()
{
    App app;
    app.update();
}