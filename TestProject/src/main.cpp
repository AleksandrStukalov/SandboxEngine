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
    Cube(SE::Texture* texture1, SE::Texture* texture2, SE::Shader* shader)
        : Object(vertexInit(), 36),
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
    float mixValue{ 0.0f };
};


class App : public SE::Application
{
public:

    App()
        : Application("App", 1920, 1080)
    {
        camera.reset(new SE::Camera());

        cube.reset(new Cube((new SE::Texture("resources/textures/sand.png")), (new SE::Texture("resources/textures/sod.jpg", true)),(new SE::Shader("src/shaders/basic.vert", "src/shaders/basic.frag"))));

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
        cube->onUpdate();
        // Toggling camera mode:
        if (cameraMode)  window.setCursorMode(SE::CursorMode::CAPTURE);
        else             window.setCursorMode(SE::CursorMode::STANDARD);


        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 100.0f);
        glm::mat4 mvp = projection * view * cube->getModel();
        cube->shader.setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);

        renderer.clear(0.2f, 0.2f, 0.2f);

        // Starting imgui frame:
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("##");

            ImGui::Text("Cube:");
            ImGui::SliderFloat("Mix value", &cube->mixValue, 0, 1);
            ImGui::SliderFloat3("Position", &cube->position.x, -5, 5);
            ImGui::SliderFloat("Size", &cube->size, 0, 1);
            ImGui::SliderFloat3("Rotation", &cube->angle.x, 360, -360);
            ImGui::Text("Camera:");
            ImGui::Text("Press 'C' to enable camera mode");
            ImGui::SliderFloat("Speed", &camera->speed, 0, 5);
            ImGui::SliderFloat("Zoom", &camera->FOV, 10.0f, 90.0f);

            ImGui::End();
        }
        ImGui::Render();

        // Rendering our data:
        renderer.draw(*cube.get());


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
    std::unique_ptr<Cube> cube;
};
int main()
{
    App().update();
}