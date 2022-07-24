#include "SandboxEngine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <sstream>
#include <memory>

struct Vector2f
{
    union {
        float x;
        float r;
        float s;
    };
    union {
        float y;
        float g;
        float t;
    };

    Vector2f(float x, float y)
        : x{ x }, y{ y } {}
    Vector2f(float value)
        : x{value}, y{value} {}
};
struct Vector3f
{
    union {
        float x;
        float r;
        float s;
    };
    union {
        float y;
        float g;
        float t;
    };
    union {
        float z;
        float b;
        float r;
    };

    Vector3f(float x, float y, float z)
        : x{x}, y{y}, z{z} {}
    Vector3f(float value)
        : x{value}, y{value}, z{value} {}
};

float mixValue(0.5f);
float scaleFactor(0.5f);
Vector2f translationFactor(0.0f);

struct Vertex
{
    Vector3f position;
    Vector3f color;
    Vector2f texPos;

    Vertex(Vector3f position, Vector3f color, Vector2f texPos)
        : position(position), color(color), texPos(texPos) {}
};
class App : public SE::Application
{
public:

    App()
        : Application("App", 800, 600)
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
        shader->setUniform(SE::FLOAT, "u_scaleFactor", (void*)&scaleFactor);
        shader->setUniform(SE::FLOAT_VEC2, "u_translationFactor", (void*)&translationFactor);

        renderer.clear(0.2f, 0.2f, 0.2f);


        // Starting imgui frame:
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("##");

            ImGui::SliderFloat("Mix value", &mixValue, 0, 1);
            ImGui::SliderFloat("Size", &scaleFactor, 0.2, 1.5);
            ImGui::SliderFloat2("Translation", &translationFactor.x, -1.0f, 1.0f);

            ImGui::End();
        }
        ImGui::Render();


        std::vector<SE::Texture*> textures{ texture1.get(), texture2.get() };
        renderer.draw(*va.get(), *ib.get(), *shader.get(), textures);


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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