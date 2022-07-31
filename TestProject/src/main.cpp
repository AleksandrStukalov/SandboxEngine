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
#include <array>

bool cameraMode(false);

SE::Vertex* getCube(glm::vec3 pos, float size)
{
    return new SE::Vertex[36]
    {
        //// VertPos            // TexPos                      // Index
        // Near:
        { { pos.x - size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    0
        { { pos.x - size / 2, pos.y + size / 2, pos.z + size / 2 },    { 0, 1 } },     // Top left     1
        { { pos.x + size / 2, pos.y + size / 2, pos.z + size / 2 },    { 1, 1 } },     // Top right    2

        { { pos.x + size / 2, pos.y + size / 2, pos.z + size / 2 },    { 1, 1 } },     // Top right    2
        { { pos.x + size / 2, pos.y - size / 2, pos.z + size / 2 },    { 1, 0 } },     // Down right   3
        { { pos.x - size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    0

        // Far
        { { pos.x - size / 2, pos.y - size / 2, pos.z - size / 2 },    { 0, 0 } },     // Down left    4
        { { pos.x - size / 2, pos.y + size / 2, pos.z - size / 2 },    { 0, 1 } },     // Top left     5
        { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    6

        { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    6
        { { pos.x + size / 2, pos.y - size / 2, pos.z - size / 2 },    { 1, 0 } },     // Down right   7
        { { pos.x - size / 2, pos.y - size / 2, pos.z - size / 2 },    { 0, 0 } },     // Down left    4

        // Left
        { { pos.x - size / 2, pos.y - size / 2, pos.z - size / 2 },    { 0, 0 } },     // Down left    8
        { { pos.x - size / 2, pos.y + size / 2, pos.z - size / 2 },    { 0, 1 } },     // Top left     9
        { { pos.x - size / 2, pos.y + size / 2, pos.z + size / 2 },    { 1, 1 } },     // Top right    10

        { { pos.x - size / 2, pos.y + size / 2, pos.z + size / 2 },    { 1, 1 } },     // Top right    10
        { { pos.x - size / 2, pos.y - size / 2, pos.z + size / 2 },    { 1, 0 } },     // Down right   11
        { { pos.x - size / 2, pos.y - size / 2, pos.z - size / 2 },    { 0, 0 } },     // Down left    8
        
        // Right
        { { pos.x + size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    12
        { { pos.x + size / 2, pos.y + size / 2, pos.z + size / 2 },    { 0, 1 } },     // Top left     13
        { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    14

        { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    14
        { { pos.x + size / 2, pos.y - size / 2, pos.z - size / 2 },    { 1, 0 } },     // Down right   15
        { { pos.x + size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    12
        // Top
        { { pos.x - size / 2, pos.y + size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    16
        { { pos.x - size / 2, pos.y + size / 2, pos.z - size / 2 },    { 0, 1 } },     // Top left     17
        { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    18
        
        { { pos.x + size / 2, pos.y + size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    18
        { { pos.x + size / 2, pos.y + size / 2, pos.z + size / 2 },    { 1, 0 } },     // Down right   19
        { { pos.x - size / 2, pos.y + size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    16
        
        // Bottom
        { { pos.x - size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 0 } },     // Down left    20
        { { pos.x - size / 2, pos.y - size / 2, pos.z - size / 2 },    { 0, 1 } },     // Top left     21
        { { pos.x + size / 2, pos.y - size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    22

        { { pos.x + size / 2, pos.y - size / 2, pos.z - size / 2 },    { 1, 1 } },     // Top right    22
        { { pos.x + size / 2, pos.y - size / 2, pos.z + size / 2 },    { 1, 0 } },     // Down right   23
        { { pos.x - size / 2, pos.y - size / 2, pos.z + size / 2 },    { 0, 0 } }      // Down left    20
    };
}

glm::vec3 firstCubePos(1.0f, -5.0f, 0.0f);
float firstCubeSize(1.0f);

glm::vec3 secondCubePos(0.0f, 5.0f, 0.0f);
float secondCubeSize(1.0f);

const static unsigned int cubeCount = 2;
const unsigned int vertexCount = cubeCount * 36;

class App : public SE::Application
{
public:
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

    App()
        : Application("App", 1920, 1080)
        , camera(new SE::Camera(glm::vec3(0, 0, 20)))
        , sand(new SE::Texture("resources/textures/sand.png"))
        , sod(new SE::Texture("resources/textures/sod.jpg", true))
        , shader(new SE::Shader("src/shaders/basic.vert", "src/shaders/basic.frag"))
        , mesh(new SE::Mesh(nullptr, sizeof(SE::Vertex) * 36 * cubeCount, SE::DYNAMIC_DRAW)) // Just allocating space)
    {
        {
            //unsigned int indices[indexCount];
            //unsigned int offset{ 0 };
            //for (unsigned int i{}; i < indexCount; i += 36)
            //{
            //    // Near:
            //    indices[i + 0] = offset + 0;
            //    indices[i + 1] = offset + 1;
            //    indices[i + 2] = offset + 2;

            //    indices[i + 3] = offset + 2;
            //    indices[i + 4] = offset + 3;
            //    indices[i + 5] = offset + 0;

            //    // Far:
            //    indices[i + 6] = offset + 4;
            //    indices[i + 7] = offset + 5;
            //    indices[i + 8] = offset + 6;

            //    indices[i + 9] = offset + 6;
            //    indices[i + 10] = offset + 7;
            //    indices[i + 11] = offset + 4;

            //    // Left:
            //    indices[i + 12] = offset + 8;
            //    indices[i + 13] = offset + 9;
            //    indices[i + 14] = offset + 10;

            //    indices[i + 15] = offset + 10;
            //    indices[i + 16] = offset + 11;
            //    indices[i + 17] = offset + 8;

            //    // Right:
            //    indices[i + 18] = offset + 12;
            //    indices[i + 19] = offset + 13;
            //    indices[i + 20] = offset + 14;

            //    indices[i + 21] = offset + 14;
            //    indices[i + 22] = offset + 15;
            //    indices[i + 23] = offset + 12;

            //    // Top:
            //    indices[i + 24] = offset + 16;
            //    indices[i + 25] = offset + 17;
            //    indices[i + 26] = offset + 18;

            //    indices[i + 27] = offset + 18;
            //    indices[i + 28] = offset + 19;
            //    indices[i + 29] = offset + 16;

            //    // Bottom:
            //    indices[i + 30] = offset + 20;
            //    indices[i + 31] = offset + 21;
            //    indices[i + 32] = offset + 22;

            //    indices[i + 33] = offset + 22;
            //    indices[i + 34] = offset + 23;
            //    indices[i + 35] = offset + 20;
            //}

            //ib.reset(new SE::IndexBuffer(indices, SE::UNSIGNED_INT, sizeof(indices), SE::STATIC_DRAW));
        }
            
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
                ImGui::Begin("Camera");
                ImGui::Text("Press 'C' to toggle camera mode");
                ImGui::Text("Scroll to adjust speed");
                ImGui::Text("Speed: %i", (int)camera->speed);
                ImGui::End();

                ImGui::Begin("First cube");
                ImGui::SliderFloat3("Position", &firstCubePos.x, -10.0f, 10.0f);
                ImGui::SliderFloat("Size", &firstCubeSize, 0.5f, 5.0f);
                ImGui::End();

                ImGui::Begin("Second cube");
                ImGui::SliderFloat3("Position", &secondCubePos.x, -10.0f, 10.0f);
                ImGui::SliderFloat("Size", &secondCubeSize, 0.5f, 5.0f);
                ImGui::End();
            }
            ImGui::Render();
        }

        // Transforming & Rendering:
        {
            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 100.0f);
            glm::mat4 vp = projection * view;
            shader->setUniform(SE::MAT4F, "u_transformation", (void*)&vp);

            std::unique_ptr<SE::Vertex> firstCubeVertices(getCube(firstCubePos, firstCubeSize));
            std::unique_ptr<SE::Vertex> secondCubeVertices(getCube(secondCubePos, secondCubeSize));

            // Setting dynamic VB:
            mesh->vb.bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(SE::Vertex) * 36, firstCubeVertices.get());
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(SE::Vertex) * 36, sizeof(SE::Vertex) * 36, secondCubeVertices.get());


            //Rendering:
            renderer.draw(*mesh.get(), *shader.get(), *sod.get());
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    std::unique_ptr<SE::Camera> camera;
    std::unique_ptr<SE::Texture> sand;
    std::unique_ptr<SE::Texture> sod;
    std::unique_ptr<SE::Shader> shader;
    std::unique_ptr<SE::Mesh> mesh;
};

int main()
{
    App().update();
}