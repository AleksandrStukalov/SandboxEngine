#pragma once

#include "SandboxEngine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <sstream>
#include <memory>

bool cameraMode(false);

class App : public SE::Application
{
public:

    App()
        : Application("App", 1920, 1080)
        , camera(new SE::Camera(glm::vec3(0, 0, 20)))
        , sand(new SE::Texture("resources/textures/sand.png"))
        , sod(new SE::Texture("resources/textures/sod.jpg", true))
        , shader(new SE::Shader("src/shaders/basic.vert", "src/shaders/basic.frag"))
        , mesh(new SE::Mesh(nullptr, 36 * sizeof(SE::Vertex), SE::DYNAMIC_DRAW)) // Just allocating space)
    {
        unsigned int indices[]
        {
            // Near:
            0, 1, 2,
            2, 3, 0,
            // Far:
            4, 5, 6,
            6, 7, 4,
            // Left:
            8, 9, 10,
            10, 11, 8,
            // Right:
            12, 13, 14,
            14, 15, 12,
            // Top:
            16, 17, 18,
            18, 19, 16,
            // Bottom:
            20, 21, 22,
            22, 23, 20
        };
        ib.reset(new SE::IndexBuffer(indices, SE::UNSIGNED_INT, sizeof(indices)));

        // Initializing ImGui:
        {
            // Setting up ImGui context:
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ImGui::StyleColorsDark();

            // Initializing ImGui for our platform:
            ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window.handle, true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }
    }

    ~App()
    {
        // Finilizing ImGui:
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }

    void onUpdate() override
    {
        // Toggling camera mode:
        if (cameraMode)  window.setCursorMode(SE::CursorMode::CAPTURE);
        else             window.setCursorMode(SE::CursorMode::STANDARD);

        renderer.clear(0.2f, 0.2f, 0.2f);
        // Creating UI:
        {
            // Starting imgui frame:
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            {
                ImGui::Begin("##");
                ImGui::Text("Camera:");
                ImGui::Text("Press 'C' to toggle camera mode");
                ImGui::Text("Scroll to adjust speed");
                ImGui::Text("Speed: %i", (int)camera->speed);

                ImGui::End();
            }
            ImGui::Render();
        }

        // Transforming & Rendering:
        {
            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 100.0f);
            glm::mat4 model(1.0f);
            glm::mat4 mvp = projection * view * model;
            shader->setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);

            SE::Vertex vertices[36]
            {
                //// VertPos            // TexPos                       // Index
                // Near:
                { { -0.5, -0.5, 0.5 },  { 0, 0 } },     // Down left    0
                { { -0.5, 0.5, 0.5 },   { 0, 1 } },     // Top left     1
                { { 0.5, 0.5, 0.5 },    { 1, 1 } },     // Top right    2
                { { 0.5, -0.5, 0.5 },   { 1, 0 } },     // Down right   3
                // Far
                { { 0.5, -0.5, -0.5 },  { 0, 0 } },     // Down left    4
                { { 0.5, 0.5, -0.5 },   { 0, 1 } },     // Top left     5
                { { -0.5, 0.5, -0.5 },  { 1, 1 } },     // Top right    6
                { { -0.5, -0.5, -0.5 }, { 1, 0 } },     // Down right   7
                // Left
                { { -0.5, -0.5, -0.5 }, { 0, 0 } },     // Down left    8
                { { -0.5, 0.5, -0.5 },  { 0, 1 } },    // Top left     9
                { { -0.5, 0.5,  0.5 },  { 1, 1 } },     // Top right    10
                { { -0.5, -0.5, 0.5 },  { 1, 0 } },     // Down right   11
                // Right
                { { 0.5, -0.5, 0.5 },   { 0, 0 } },     // Down left    12
                { { 0.5, 0.5, 0.5 },    { 0, 1 } },     // Top left     13
                { { 0.5, 0.5, -0.5 },   { 1, 1 } },     // Top right    14
                { { 0.5, -0.5, -0.5 },  { 1, 0 } },     // Down right   15
                // Top
                { { -0.5, 0.5, 0.5 },   { 0, 0 } },     // Down left    16
                { { -0.5, 0.5, -0.5 },  { 0, 1 } },     // Top left     17
                { { 0.5, 0.5, -0.5 },   { 1, 1 } },     // Top right    18
                { { 0.5, 0.5, 0.5 },    { 1, 0 } },     // Down right   19
                // Bottom
                { { -0.5, -0.5, -0.5 }, { 0, 0 } },     // Down left    20
                { { -0.5, -0.5, 0.5 },  { 0, 1 } },     // Top left     21
                { { 0.5, -0.5, 0.5 },   { 1, 1 } },     // Top right    22
                { { 0.5, -0.5, -0.5 },  { 1, 0 } }      // Down right   23
            };

            // Setting dynamic VB:
            mesh->vb.bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            //Rendering:
            renderer.draw(*mesh.get(), *ib.get(), *shader.get(), *sod.get());
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void processKeyboard() override
    {
        cameraMode = events.isKey(SE::Key::C, SE::Action::TOGGLE);

        if (cameraMode) camera->processKeyboard(events, deltaTime);
    }
    void processMouseMovement(float xoffset, float yoffset) override
    {
        if (cameraMode) camera->processMouseMovement(xoffset, yoffset);
    }
    void processScroll(float offset) override
    {
        if (cameraMode) camera->processScroll(offset);
    }

    
    std::unique_ptr<SE::Camera> camera;
    std::unique_ptr<SE::Texture> sand;
    std::unique_ptr<SE::Texture> sod;
    std::unique_ptr<SE::Shader> shader;
    std::unique_ptr<SE::Mesh> mesh;
    std::unique_ptr<SE::IndexBuffer> ib;
};

int main()
{
    App().update();
}