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
        float positions[]
        {
            -0.5f, -0.5f, 0.0f,  // Left
             0.0f, 0.5f, 0.0f,   // Top
             0.5f, -0.5f, 0.0f   // Right
        };

        vb.reset(new SE::VertexBuffer(positions, sizeof(positions)));

        glGenVertexArrays(1, &va);
        glBindVertexArray(va);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, (void*)0);
        glEnableVertexAttribArray(0);

    }

    ~App()
    {
        glDeleteVertexArrays(1, &va);
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

        glDrawArrays(GL_TRIANGLES, 0, 3);

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
};

int main()
{
    App app;
    app.update();
}