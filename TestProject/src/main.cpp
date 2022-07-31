#pragma once

#include "Voxels.h"

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

struct Chunk2 : public Chunk
{
    void setTypes() override
    {
        for (int x{}; x < this->count; ++x)
            for (int y{}; y < this->count; ++y)
                for (int z{}; z < this->count; ++z)
                    this->voxels[x][y][z].type = VoxelType::SAND;
    }
};

class App : public SE::Application
{
public:
    void processKeyboard() override
    {
        cameraMode = events.isKey(SE::Key::C, SE::Action::TOGGLE);

        if (cameraMode) camera.processKeyboard(events, deltaTime);
    }
    void processMouseMovement(float xoffset, float yoffset) override
    {
        if (cameraMode) camera.processMouseMovement(xoffset, yoffset);
    }
    void processScroll(float offset) override
    {
        if (cameraMode) camera.processScroll(offset);
    }

    App()
        : Application("App", 1920, 1080)
    {
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
                ImGui::Text("Speed: %i", (int)camera.speed);
                ImGui::End();
            }
            ImGui::Render();
        }

        // Transforming & Rendering:
        {
            glm::mat4 view = camera.getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), (float)window.width / (float)window.height, 0.1f, 100.0f);
            glm::mat4 vp = projection * view;
            shader.setUniform(SE::MAT4F, "u_transformation", (void*)&vp);

            //Rendering:
            shader.setUniform(SE::INT, "u_texture", (void*)&sand.slot);
            renderer.draw(*chunk.getMesh(), chunk.ib, shader, sand);
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    SE::Camera camera{ glm::vec3(0, 0, 20) };
    SE::Texture sod{ "D:/Development/SandboxEngine/TestProject/resources/textures/sod.jpg", true };
    SE::Texture sand{ "D:/Development/SandboxEngine/TestProject/resources/textures/sand.png" };
    SE::Shader shader{ "D:/Development/SandboxEngine/TestProject/src/shaders/basic.vert", "D:/Development/SandboxEngine/TestProject/src/shaders/basic.frag" };
    Chunk2 chunk;
}; 

int main()
{
    App().update();
}

