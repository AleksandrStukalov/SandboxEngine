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

// Camera:
bool cameraMode(false);


class Cube : public SE::Object
{
public:
    Cube(SE::Texture* texture1, SE::Texture* texture2, SE::Shader* shader, glm::vec3 position = glm::vec3(0.0f), glm::vec3 angle = glm::vec3(0.0f), float size = 1.0f)
        : Object(vertexInit(), 36, position, angle, size),
        texture1(*texture1),
        texture2(*texture2),
        shader(*shader)
    {       
        this->shader.setUniform(SE::INT, "u_texture1", (void*)&this->texture1.slot);
        this->shader.setUniform(SE::INT, "u_texture2", (void*)&this->texture2.slot);
    }
    SE::Vertex* vertexInit() override
    {
        SE::Vertex* vertices = new SE::Vertex[36];
        //                       // Positions         // TexPos
        // Near:
        vertices[0] = SE::Vertex({ -0.5, -0.5, 0.5 }, { 0, 0 });     // Down left 
        vertices[1] = SE::Vertex({ -0.5, 0.5, 0.5 }, { 0, 1 });     // Top left  
        vertices[2] = SE::Vertex({ 0.5, 0.5, 0.5 }, { 1, 1 });     // Top right 

        vertices[3] = SE::Vertex({ 0.5, 0.5, 0.5 }, { 1, 1 });     // Top right 
        vertices[4] = SE::Vertex({ 0.5, -0.5, 0.5 }, { 1, 0 });     // Down right
        vertices[5] = SE::Vertex({ -0.5, -0.5, 0.5 }, { 0, 0 });     // Down left 

        // Far:
        vertices[6] = SE::Vertex({ 0.5, -0.5, -0.5 }, { 0, 0 });     // Down right
        vertices[7] = SE::Vertex({ 0.5, 0.5, -0.5 }, { 0, 1 });     // Top right 
        vertices[8] = SE::Vertex({ -0.5, 0.5, -0.5 }, { 1, 1 });     // Top left  

        vertices[9] = SE::Vertex({ -0.5, 0.5, -0.5 }, { 1, 1 });     // Top left  
        vertices[10] = SE::Vertex({ -0.5, -0.5, -0.5 }, { 1, 0 });     // Down left 
        vertices[11] = SE::Vertex({ 0.5, -0.5, -0.5 }, { 0, 0 });     // Down right

        // Left:
        vertices[12] = SE::Vertex({ -0.5, -0.5, -0.5 }, { 0, 0 });     // Down left 
        vertices[13] = SE::Vertex({ -0.5, 0.5, -0.5 }, { 0, 1 });     // Top left  
        vertices[14] = SE::Vertex({ -0.5, 0.5, 0.5 }, { 1, 1 });     // Top left  

        vertices[15] = SE::Vertex({ -0.5, 0.5, 0.5 }, { 1, 1 });     // Top left  
        vertices[16] = SE::Vertex({ -0.5, -0.5, 0.5 }, { 1, 0 });     // Down left 
        vertices[17] = SE::Vertex({ -0.5, -0.5, -0.5 }, { 0, 0 });     // Down left 

        // Right:
        vertices[18] = SE::Vertex({ 0.5, -0.5, 0.5 }, { 0, 0 });     // Down right
        vertices[19] = SE::Vertex({ 0.5, 0.5, 0.5 }, { 0, 1 });     // Top right 
        vertices[20] = SE::Vertex({ 0.5, 0.5, -0.5 }, { 1, 1 });     // Top right 
        vertices[21] = SE::Vertex({ 0.5, 0.5, -0.5 }, { 1, 1 });     // Top right 
        vertices[22] = SE::Vertex({ 0.5, -0.5, -0.5 }, { 1, 0 });     // Down right
        vertices[23] = SE::Vertex({ 0.5, -0.5, 0.5 }, { 0, 0 });     // Down right

        // Top:
        vertices[24] = SE::Vertex({ -0.5, 0.5, 0.5 }, { 0, 0 });     // Top left  
        vertices[25] = SE::Vertex({ -0.5, 0.5, -0.5 }, { 0, 1 });     // Top left  
        vertices[26] = SE::Vertex({ 0.5, 0.5, -0.5 }, { 1, 1 });     // Top right 

        vertices[27] = SE::Vertex({ 0.5, 0.5, -0.5 }, { 1, 1 });     // Top right 
        vertices[28] = SE::Vertex({ 0.5, 0.5, 0.5 }, { 1, 0 });     // Top right 
        vertices[29] = SE::Vertex({ -0.5, 0.5, 0.5 }, { 0, 0 });     // Top left  

        // Bottom:
        vertices[30] = SE::Vertex({ 0.5, -0.5, -0.5 }, { 1, 0 });     // Down right
        vertices[31] = SE::Vertex({ -0.5, -0.5, -0.5 }, { 0, 0 });     // Down left 
        vertices[32] = SE::Vertex({ -0.5, -0.5, 0.5 }, { 0, 1 });     // Down left 

        vertices[33] = SE::Vertex({ -0.5, -0.5, 0.5 }, { 0, 1 });     // Down left 
        vertices[34] = SE::Vertex({ 0.5, -0.5, 0.5 }, { 1, 1 });     // Down right
        vertices[35] = SE::Vertex({ 0.5, -0.5, -0.5 }, { 1, 0 });     // Down right

        return vertices;
    }

    void onUpdate() override
    {
        shader.setUniform(SE::FLOAT, "mixValue", (void*)&mixValue);
    }

    void bind() override
    {
        va.bind();
        shader.bind();
        texture1.bind();
        texture2.bind();
    }



    SE::Texture& texture1;
    SE::Texture& texture2;
    SE::Shader&  shader;
    float mixValue{ 0.5f };
};

const unsigned int cubeCount{ 10 };
float mixValue{ 0.5f };

class App : public SE::Application
{
public:

    App()
        : Application("App", 1920, 1080)
    {
        camera.reset(new SE::Camera());
        SE::Texture* texture1 = new SE::Texture("resources/textures/sand.png", false);
        SE::Texture* texture2 = new SE::Texture("resources/textures/sod.jpg", true);
        SE::Shader* shader = new SE::Shader("src/shaders/basic.vert", "src/shaders/basic.frag");

        // Filling cube array:
        for (int i{}; i < cubeCount; ++i)
            for (int j{}; j < cubeCount; ++j)
                for (int k{}; k < cubeCount; ++k)
                    cubes[i][j][k].reset(new Cube(texture1, texture2, shader, glm::vec3(i,j,k)));


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
        // Toggling camera mode:
        if (cameraMode)  window.setCursorMode(SE::CursorMode::CAPTURE);
        else             window.setCursorMode(SE::CursorMode::STANDARD);


        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 100.0f);

        renderer.clear(0.2f, 0.2f, 0.2f);
        {
        // Starting imgui frame:
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("##");
            ImGui::Text("Camera:");
            ImGui::Text("Press 'C' to toggle camera mode");
            ImGui::SliderFloat("Speed", &camera->speed, 0, 5);
            ImGui::Text("Cubes:");
            ImGui::SliderFloat("Mix value", &mixValue, 0, 1);

            ImGui::End();
        }
        ImGui::Render();

        }

        // Updating and rendering cubes:
        for (int i{}; i < cubeCount; ++i)
            for (int j{}; j < cubeCount; ++j)
                for (int k{}; k < cubeCount; ++k)
                {
                    auto& cube = *cubes[i][j][k].get();
                    cube.mixValue = mixValue;
                    cube.onUpdate();
                    glm::mat4 mvp = projection * view * cube.getModel();
                    cube.shader.setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);
                    renderer.draw(cube);
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
    std::unique_ptr<Cube> cubes[cubeCount][cubeCount][cubeCount];
};
int main()
{
    App().update();
}