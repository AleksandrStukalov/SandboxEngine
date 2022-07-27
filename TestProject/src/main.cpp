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

#include <random>
#include <process.h>
#define RAND rand() / (float)RAND_MAX

// Object:
float mixValue(0.0f);
glm::vec3 position(0.0f);
float size(0.5f);
glm::vec3 objPos(0.0f, 0.0f, -3.0f);
glm::vec3 angle(0.0f);

// Camera:
bool cameraMode(false);

struct Vertex
{
    SE::Vec3f position;
    SE::Vec3f color;
    SE::Vec2f texPos;

    Vertex(){}
    Vertex(SE::Vec3f position, SE::Vec3f color, SE::Vec2f texPos)
        : position(position), color(color), texPos(texPos) {}
    Vertex(SE::Vec3f position, SE::Vec2f texPos)
        : position(position), color(RAND, RAND, RAND), texPos(texPos) {}
};
class App : public SE::Application
{
public:

    App()
        : Application("App", 1920, 1080)
    {
        Vertex vertices[36];
        {
                                 // Positions           // TexPos
            // Near:
            vertices[0] = Vertex({ -0.5, -0.5, 0.5 },   { 0, 0 });     // Down left 
            vertices[1] = Vertex({ -0.5, 0.5, 0.5 },    { 0, 1 });     // Top left  
            vertices[2] = Vertex({ 0.5, 0.5, 0.5 },     { 1, 1 });     // Top right 

            vertices[3] = Vertex({ 0.5, 0.5, 0.5 },     { 1, 1 });     // Top right 
            vertices[4] = Vertex({ 0.5, -0.5, 0.5 },    { 1, 0 });     // Down right
            vertices[5] = Vertex({ -0.5, -0.5, 0.5 },   { 0, 0 });     // Down left 

            // Far:
            vertices[6] = Vertex({ 0.5, -0.5, -0.5 },   { 0, 0 });     // Down right
            vertices[7] = Vertex({ 0.5, 0.5, -0.5 },    { 0, 1 });     // Top right 
            vertices[8] = Vertex({ -0.5, 0.5, -0.5 },   { 1, 1 });     // Top left  

            vertices[9] = Vertex({ -0.5, 0.5, -0.5 },   { 1, 1 });     // Top left  
            vertices[10] = Vertex({ -0.5, -0.5, -0.5 }, { 1, 0 });     // Down left 
            vertices[11] = Vertex({ 0.5, -0.5, -0.5 },  { 0, 0 });     // Down right

            // Left:
            vertices[12] = Vertex({ -0.5, -0.5, -0.5 }, { 0, 0 });     // Down left 
            vertices[13] = Vertex({ -0.5, 0.5, -0.5 },  { 0, 1 });     // Top left  
            vertices[14] = Vertex({ -0.5, 0.5, 0.5 },   { 1, 1 });     // Top left  

            vertices[15] = Vertex({ -0.5, 0.5, 0.5 },   { 1, 1 });     // Top left  
            vertices[16] = Vertex({ -0.5, -0.5, 0.5 },  { 1, 0 });     // Down left 
            vertices[17] = Vertex({ -0.5, -0.5, -0.5 }, { 0, 0 });     // Down left 

            // Right:
            vertices[18] = Vertex({ 0.5, -0.5, 0.5 },   { 0, 0 });     // Down right
            vertices[19] = Vertex({ 0.5, 0.5, 0.5 },    { 0, 1 });     // Top right 
            vertices[20] = Vertex({ 0.5, 0.5, -0.5 },   { 1, 1 });     // Top right 
            vertices[21] = Vertex({ 0.5, 0.5, -0.5 },   { 1, 1 });     // Top right 
            vertices[22] = Vertex({ 0.5, -0.5, -0.5 },  { 1, 0 });     // Down right
            vertices[23] = Vertex({ 0.5, -0.5, 0.5 },   { 0, 0 });     // Down right

            // Top:
            vertices[24] = Vertex({ -0.5, 0.5, 0.5 },   { 0, 0 });     // Top left  
            vertices[25] = Vertex({ -0.5, 0.5, -0.5 },  { 0, 1 });     // Top left  
            vertices[26] = Vertex({ 0.5, 0.5, -0.5 },   { 1, 1 });     // Top right 

            vertices[27] = Vertex({ 0.5, 0.5, -0.5 },   { 1, 1 });     // Top right 
            vertices[28] = Vertex({ 0.5, 0.5, 0.5 },    { 1, 0 });     // Top right 
            vertices[29] = Vertex({ -0.5, 0.5, 0.5 },   { 0, 0 });     // Top left  

            // Bottom:
            vertices[30] = Vertex({ 0.5, -0.5, -0.5 },  { 1, 0 });     // Down right
            vertices[31] = Vertex({ -0.5, -0.5, -0.5 }, { 0, 0 });     // Down left 
            vertices[32] = Vertex({ -0.5, -0.5, 0.5 },  { 0, 1 });     // Down left 

            vertices[33] = Vertex({ -0.5, -0.5, 0.5 },  { 0, 1 });     // Down left 
            vertices[34] = Vertex({ 0.5, -0.5, 0.5 },   { 1, 1 });     // Down right
            vertices[35] = Vertex({ 0.5, -0.5, -0.5 },  { 1, 0 });     // Down right

        }

        camera.reset(new SE::Camera());

        shader.reset(new SE::Shader("src/shaders/basic.vert", "src/shaders/basic.frag"));
        texture1.reset(new SE::Texture("resources/textures/sand.png"));
        texture2.reset(new SE::Texture("resources/textures/sod.jpg", true));

        shader->setUniform(SE::INT, "u_texture1", (void*)&texture1->slot);
        shader->setUniform(SE::INT, "u_texture2", (void*)&texture2->slot);

        vb.reset(new SE::VertexBuffer(vertices, sizeof(vertices)));
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
        // Toggling camera mode:
        if (cameraMode)  window.setCursorMode(SE::CursorMode::CAPTURE);
        else             window.setCursorMode(SE::CursorMode::STANDARD);


        shader->setUniform(SE::FLOAT, "mixValue", (void*)&mixValue);
        
        // ** Transformations:
        // * Model:
        // Scaling:
        glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size, size, size));

        // Rotation:
        glm::mat4 rotation(1.0f);
        rotation = glm::rotate(rotation, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));

        // Translation:
        glm::mat4 translation = glm::translate(glm::mat4(1), position);

        glm::mat4 model = translation * rotation * scale;

        // * View
        glm::mat4 view = camera->getViewMatrix();

        // * Projection:
        glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 100.0f);

        glm::mat4 mvp = projection * view * model;
        shader->setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);

        renderer.clear(0.2f, 0.2f, 0.2f);

        // Starting imgui frame:
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("##");

            ImGui::Text("Object:");
            ImGui::SliderFloat("Mix value", &mixValue, 0, 1);
            ImGui::SliderFloat3("Position", &position.x, -5, 5);
            ImGui::SliderFloat("Size", &size, 0, 1);
            ImGui::SliderFloat3("Rotation", &angle.x, 360, -360);
            ImGui::Text("Camera:");
            ImGui::Text("Press 'C' to enable camera mode");
            ImGui::SliderFloat("Speed", &camera->speed, 0, 5);
            ImGui::SliderFloat("Zoom", &camera->FOV, 10.0f, 90.0f);

            ImGui::End();
        }
        ImGui::Render();

        // Rendering out data:
        std::vector<SE::Texture*> textures{ texture1.get(), texture2.get() };
        renderer.draw(*va.get(), *shader.get(), textures, 36);


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

    std::unique_ptr<SE::VertexBuffer> vb;
    std::unique_ptr<SE::VertexArray> va;
    std::unique_ptr<SE::Shader> shader;
    std::unique_ptr<SE::Texture> texture1;
    std::unique_ptr<SE::Texture> texture2;
    std::unique_ptr<SE::Camera> camera;
};

int main()
{
    App app;
    app.update();
}