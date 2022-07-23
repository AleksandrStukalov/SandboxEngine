#include "SandboxEngine.h"

#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <memory>

unsigned int vb, va;

class App : public SE::Application
{
public:

    App()
        : Application("App", 800, 600)
    {
        float vertices[]
        {
            -0.5f, -0.5f, 0.0f,  // Left
             0.0f, 0.5f, 0.0f,   // Top
             0.5f, -0.5f, 0.0f   // Right
        };

        vb.reset(new SE::VertexBuffer(vertices, sizeof(vertices)));

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

        renderer.draw(*va.get());

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
};

int main()
{
    App app;
    app.update();
}