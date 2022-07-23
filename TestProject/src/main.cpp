#include "SandboxEngine.h"

#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <memory>

float mixValue(0.5f);

class App : public SE::Application
{
public:

    App()
        : Application("App", 800, 600)
    {
        float vertices[]
        {
            // Positions         // Colors           // TexPos
            -0.5f, -0.5f, 0.0f,  0.1f, 0.2f, 0.9f,    0.0f, 0.0f,       // Bottom left
             -0.5f, 0.5f, 0.0f,  0.5f, 0.65f, 0.1f,   0.0f, 1.0f,       // Top left
             0.5f, 0.5f, 0.0f,   0.67f, 0.24f, 0.8f,  1.0f, 1.0f,       // Top right
             0.5f, -0.5f, 0.0f,  0.1f, 0.9f, 0.5f,    1.0f, 0.0f        // Bottom right
        };

        unsigned int indices[]
        { 
            0,1,2,
            2,3,0 
        };

        shader.reset(new SE::Shader("src/shaders/basic.vert", "src/shaders/basic.frag"));
        texture1.reset(new SE::Texture("resources/textures/sand.png"));
        texture2.reset(new SE::Texture("resources/textures/sod.jpg", true));

        shader->setUniform(SE::INT, "u_texture1", (void*)&texture1->slot);
        shader->setUniform(SE::INT, "u_texture2", (void*)&texture2->slot);
        shader->setUniform(SE::FLOAT, "mixValue", (void*)&mixValue);

        vb.reset(new SE::VertexBuffer(vertices, sizeof(vertices)));
        ib.reset(new SE::IndexBuffer(indices, SE::UNSIGNED_INT, sizeof(indices)));
        va.reset(new SE::VertexArray());

        SE::VertexAttribute positions(3, SE::FLOAT);
        SE::VertexAttribute colors(3, SE::FLOAT);
        SE::VertexAttribute texPos(2, SE::FLOAT);
        SE::VertexBufferLayout layout;
        layout.add(positions);
        layout.add(colors);
        layout.add(texPos);

        va.get()->add(*vb.get(), layout);

    }

    ~App()
    {
       
    }

    void onUpdate() override
    {
        if (events.isKey(SE::Key::A, SE::Action::PRESSED)) SE::Log::info({ "A pressed" });
        if (events.isMouseButton(SE::MouseButton::LEFT, SE::Action::PRESSED)) SE::Log::info({ "LMB" });
        shader->setUniform(SE::FLOAT, "mixValue", (void*)&mixValue);

        renderer.clear(0.2f, 0.2f, 0.2f);

        std::vector<SE::Texture*> textures{ texture1.get(), texture2.get() };
        renderer.draw(*va.get(), *ib.get(), *shader.get(), textures);

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

    void processScroll(float offset) override
    {
        float scalar(0.05f);
        mixValue += offset * scalar;
    }

    std::unique_ptr<SE::VertexBuffer> vb;
    std::unique_ptr<SE::VertexArray> va;
    std::unique_ptr<SE::IndexBuffer> ib;
    std::unique_ptr<SE::Shader> shader;
    std::unique_ptr<SE::Texture> texture1;
    std::unique_ptr<SE::Texture> texture2;
};

int main()
{
    App app;
    app.update();
}