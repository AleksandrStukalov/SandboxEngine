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
#include <cmath>
#include <array>
#include <vector>


void setVoxelMaterials(Chunk& chunk)
{
    for (int x{}; x < Chunk::voxelCount; ++x)
        for (int y{}; y < Chunk::voxelCount; ++y)
            for (int z{}; z < Chunk::voxelCount; ++z)
            {
                Voxel& voxel = chunk.voxels[x][y][z];
                voxel.material = VoxelMaterial::AIR;
                if (y <= (sin(x * 0.6f) * 0.5f + 0.5f) * 10)
                {
                    if (y <= 6) voxel.material = VoxelMaterial::GRASS;
                    if (y <= 4) voxel.material = VoxelMaterial::GROUND;
                    if (y <= 2) voxel.material = VoxelMaterial::SAND;
                }
            }
}

void setActiosOnMaterial(Chunk& chunk, Chunk::ChunkData chunkData)
{
    for (int x{}; x < Chunk::voxelCount; ++x)
        for (int y{}; y < Chunk::voxelCount; ++y)
            for (int z{}; z < Chunk::voxelCount; ++z)
            {
                Voxel& voxel = chunk.voxels[x][y][z];
                glm::vec3 index{ x, y, z };
                // Actions on type:
                if (voxel.material == VoxelMaterial::AIR) continue;

                Chunk::VoxelData voxelData{ index, index * Voxel::size };
                Chunk::TextureAtlasData texAtlasData{ { 64, 64 }, { 1024, 1024 } };
                // NOTE: Specify index starting from bottom left corner.
                if (voxel.material == VoxelMaterial::GROUND) chunk.addVoxelToMesh(chunkData, voxelData, { 2, 15 }, texAtlasData);
                if (voxel.material == VoxelMaterial::GRASS)  chunk.addVoxelToMesh(chunkData, voxelData, { 3, 15 }, texAtlasData);
                if (voxel.material == VoxelMaterial::SAND)   chunk.addVoxelToMesh(chunkData, voxelData, { 4, 15 }, texAtlasData);
            }

}

bool cameraMode(false);

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
        camera->speed = 40.0f;


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
                ImGui::Text("   Press 'C' to toggle camera mode");
                ImGui::Text("   Scroll to adjust speed");
                ImGui::Text("   Speed: %i", (int)camera->speed);
                ImGui::Text("");
                ImGui::SliderFloat("Voxel size", &Voxel::size, 0.5, 4.0);
                ImGui::End();
            }
            ImGui::Render();
        }

        // Transforming & Rendering:
        {
            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 1000.0f);
            
            shader->setUniform(SE::INT, "u_texture", (void*)&atlas->slot);

            for (int x{}; x < ChunkManager::chunkCount; ++x)
                for (int y{}; y < ChunkManager::chunkCount; ++y)
                    for (int z{}; z < ChunkManager::chunkCount; ++z)
                    {
                        Chunk& chunk = chunkManager.chunks[x][y][z];
                        glm::mat4 model = glm::translate(glm::mat4(1.0f), { glm::vec3(x, y, z) * (float)Chunk::voxelCount * Voxel::size });
                        glm::mat4 mvp = projection * view * model;
                        shader->setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);
                        Chunk::ChunkData chunkData{ glm::ivec3(x, y, z), chunkManager.chunkCount, chunkManager.chunks };
                        renderer.draw(*chunk.getMesh(setActiosOnMaterial, chunkData), chunkManager.chunkIB, *shader.get(), *atlas.get());
                        auto c = chunkManager.chunks;
                    }
           
        }


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    std::unique_ptr<SE::Camera> camera{ new SE::Camera(glm::vec3(0, 0, 100)) };
    std::unique_ptr<SE::Texture> atlas{ new SE::Texture{ "D:/Development/SandboxEngine/TestProject/resources/textures/atlas.png", true } };
    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "D:/Development/SandboxEngine/TestProject/src/shaders/basic.vert", "D:/Development/SandboxEngine/TestProject/src/shaders/basic.frag" } };
    ChunkManager chunkManager{ setVoxelMaterials };
}; 

int main()
{
    App* app = new App;
    app->update();

    delete app;
}

