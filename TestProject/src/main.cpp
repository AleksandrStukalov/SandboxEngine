#include "SandboxEngine.h"

#include <glad/glad.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"

#include <iostream>
#include <sstream>
#include <memory>
#include <cmath>



float mixValue(0.5f);
SE::Vec2f position(0.0f);
float size(0.5f);
float radians(0.0f);

struct Vertex
{
    SE::Vec3f position;
    SE::Vec3f color;
    SE::Vec2f texPos;

    Vertex(SE::Vec3f position, SE::Vec3f color, SE::Vec2f texPos)
        : position(position), color(color), texPos(texPos) {}
};
class App : public SE::Application
{
public:

    App()
        : Application("App", 1920, 1080)
    {
        Vertex vertices[]
        {
                   // Positions              // Colors              // TexPos
            Vertex({ -0.5f, -0.5f, -0.5f},  {0.1f, 0.2f, 0.9f},     {0.0f, 0.0f}),        // Bottom left
            Vertex({-0.5f, 0.5f, 0.0f},     {0.5f, 0.65f, 0.1f},    {0.0f, 1.0f}),        // Top left
            Vertex({0.5f, 0.5f, 0.0f},      {0.67f, 0.24f, 0.8f},   {1.0f, 1.0f}),        // Top right
            Vertex({0.5f, -0.5f, 0.0f},     {0.1f, 0.9f, 0.5f},     {1.0f, 0.0f})         // Bottom right
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


        // Setting up ImGui context:
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        // Initializing ImGui for our platform:
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window.handle, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    ~App()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void onUpdate() override
    {
        shader->setUniform(SE::FLOAT, "mixValue", (void*)&mixValue);
        
        SE::Mat4f scale(size, 0.0f, 0.0f, 0.0f,
                        0.0f, size, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);
        shader->setUniform(SE::MAT4F, "u_scale", (void*)&scale);

        SE::Mat4f translation(1.0f, 0.0f, 0.0f, position.x,
                              0.0f, 1.0f, 0.0f, position.y,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);
        translation.transpose();
        shader->setUniform(SE::MAT4F, "u_translation", (void*)&translation);

        SE::Mat4f rotation(std::cos(radians), -std::sin(radians), 0.0f, 0.0f,
                           std::sin(radians), std::cos(radians), 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f,
                           0.0f, 0.0f, 0.0f, 1.0f);
        shader->setUniform(SE::MAT4F, "u_rotation", (void*)&rotation);

        renderer.clear(0.2f, 0.2f, 0.2f);

        // Starting imgui frame:
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("##");

            ImGui::SliderFloat("Mix value", &mixValue, 0, 1);
            ImGui::SliderFloat2("Position", &position.x, -1, 1);
            ImGui::SliderFloat("Size", &size, 0, 1);

            ImGui::End();
        }
        ImGui::Render();

        // Rendering out data:
        std::vector<SE::Texture*> textures{ texture1.get(), texture2.get() };
        renderer.draw(*va.get(), *ib.get(), *shader.get(), textures);


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void processKeyboard() override
    {
        float scalar(0.05);

        // Translation:
        if (events.isKey(SE::Key::W, SE::Action::PRESSED)) position.y += scalar;
        if (events.isKey(SE::Key::A, SE::Action::PRESSED)) position.x -= scalar;
        if (events.isKey(SE::Key::S, SE::Action::PRESSED)) position.y -= scalar;
        if (events.isKey(SE::Key::D, SE::Action::PRESSED)) position.x += scalar;

        // Rotation:
        if (events.isKey(SE::Key::Q, SE::Action::PRESSED)) radians -= scalar;
        if (events.isKey(SE::Key::E, SE::Action::PRESSED)) radians += scalar;
    }
    void processMouseMovement(float xoffset, float yoffset) override
    {
        
    }
    void processScroll(float offset) override
    {

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