#pragma once

#include "Voxels.h"

#include "SandboxEngine.h"

#include "SandboxEngine/Graphics/Primitives/Plane.h"
#include "SandboxEngine/Graphics/Primitives/Cube.h"
#include "SandboxEngine/Graphics/Primitives/BoundingBox.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum OctreeIndices : unsigned int
{
    BottomLeftFront = 0,
    TopLeftFront = 1,
    TopRightFront = 2,
    BottomRightFront = 3,
    BottomLeftBack = 4,
    TopLeftBack = 5,
    TopRightBack = 6,
    BottomRightBack = 7
};
//struct Octree
//{
//    Octree(const unsigned int depth)
//    {
//        Subdivide(Node(), depth);
//    }
//
//    struct Node
//    {
//
//        SE::BoundingBox bb;
//        Node* childNodes[8];
//    };
//
//    void Subdivide(Node& node, const unsigned int depth)
//    {
//        node.childNodes[BottomLeftFront]
//        
//        if (depth > 0)
//            for (auto childNode : node.childNodes)
//                Subdivide(*childNode, depth - 1);
//    }
//};

class OctreeApp : public SE::Application
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

    OctreeApp()
        : Application("OctreeApp", 1920, 1080)
    {
        camera->speed = 10.0f;

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

    ~OctreeApp()
    {
        // Finalizing ImGui:
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
                ImGui::Text("   Press 'C' to toggle camera mode");
                ImGui::Text("   Scroll to adjust speed");
                ImGui::Text("   Speed: %i", (int)camera->speed);
                ImGui::Text("Bounding box:");
                ImGui::SliderFloat("Scale", &BBScale, 0, 100);
                ImGui::End();
            }
            ImGui::Render();
        }

        // Transforming & Rendering:
        {
            // Translation:
            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 1000.0f);
            glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(BBScale));
            glm::mat4 mvp = projection * view * model;
            shader->setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);

            // Rendering:
            glm::vec3 color(0.0f, 1.0f, 0.0f);
            shader->setUniform(SE::FLOAT_VEC3, "u_color", (void*)&color);
            renderer.draw(*bb.mesh.get(), bb.ib, *shader.get(), *atlas.get(), SE::DrawMode::LINES);
        }


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    std::unique_ptr<SE::Camera> camera{ new SE::Camera(glm::vec3(0, 0, 0)) };
    std::unique_ptr<SE::Texture> atlas{ new SE::Texture{ "D:/Development/SandboxEngine/TestProject/resources/textures/atlas.png", true } };
    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.vert", "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.frag" } };
    bool cameraMode{ false };
    SE::BoundingBox bb{ 5.0f, {-5.0f, -3.0f, -17.0f}};
    float BBScale{ 1.0f };
};