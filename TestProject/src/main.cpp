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
#include <cmath>

bool cameraMode(false);

struct Chunk : public ChunkBase
{
    Chunk() { this->cubeSize = 1.0f; }
    void setVoxelType(Voxel& voxel, glm::vec3 index) override
    {
        // Setting type:
        voxel.type = VoxelType::AIR;
        float x = index.x, y = index.y, z = index.z;
        if (y <= (sin(x * 0.6f) * 0.5f + 0.5f) * 10)
        {
            if (y <= 6) voxel.type = VoxelType::GRASS;
            if (y <= 4) voxel.type = VoxelType::GROUND;
            if (y <= 2) voxel.type = VoxelType::SAND;
        }
    }

    virtual void setActiosOnType(Voxel& voxel, glm::vec3 index) override
    {
        float x = index.x, y = index.y, z = index.z;
        // Actions on type:
        if (voxel.type == VoxelType::AIR) return; // Not rendering air
        // NOTE: Specify index starting from bottom left corner.
        if (voxel.type == VoxelType::GROUND) addCube(index, cubeSize, { 2, 15 }, { 64, 64 }, { 1024, 1024 });
        if (voxel.type == VoxelType::GRASS) addCube(index, cubeSize, { 3, 15 }, { 64, 64 }, { 1024, 1024 });
        if (voxel.type == VoxelType::SAND) addCube(index, cubeSize, { 4, 15 }, { 64, 64 }, { 1024, 1024 });
    }
};

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
    {
        // Generating chunk:
        chunk->generate();


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
            }
            ImGui::Render();
        }

        // Transforming & Rendering:
        {
            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 100.0f);
            glm::mat4 vp = projection * view;
            shader->setUniform(SE::MAT4F, "u_transformation", (void*)&vp);

            //Rendering:
            shader->setUniform(SE::INT, "u_texture", (void*)&atlas->slot);
            renderer.draw(*chunk->getMesh(), *chunk->ib.get(), *shader.get(), *atlas.get());
        }


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    std::unique_ptr<SE::Camera> camera{ new SE::Camera(glm::vec3(0, 20, 40)) };
    std::unique_ptr<SE::Texture> atlas{ new SE::Texture{ "D:/Development/SandboxEngine/TestProject/resources/textures/atlas.png", true } };
    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "D:/Development/SandboxEngine/TestProject/src/shaders/basic.vert", "D:/Development/SandboxEngine/TestProject/src/shaders/basic.frag" } };
    std::unique_ptr <Chunk> chunk{new Chunk() };
}; 

int main()
{
    App().update();
}

