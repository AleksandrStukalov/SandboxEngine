#include "SandboxEngine.h"

#include <glad/glad.h>

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


float mixValue(0.5f);
glm::vec2 position(0.0f);
float size(0.5f);

glm::mat4 rotation(1.0f);
glm::vec3 angle(0.0f);
glm::vec3 prevAngle(0.0f);

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
        : Application("App", 1080, 1080)
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
        shader->setUniform(SE::FLOAT, "mixValue", (void*)&mixValue);
        
        // Scaling:
        glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size, size, size));
        shader->setUniform(SE::MAT4F, "u_scale", (void*)&scale);

        // Rotation:

        if (prevAngle.x != angle.x)
        {
            float deltaAngle = angle.x - prevAngle.x;
            rotation = glm::rotate(rotation, glm::radians(deltaAngle), glm::vec3(1, 0, 0));
            prevAngle = angle;
        }
        if (prevAngle.y != angle.y)
        {
            float deltaAngle = angle.y - prevAngle.y;
            rotation = glm::rotate(rotation, glm::radians(deltaAngle), glm::vec3(0, 1, 0));
            prevAngle = angle;
        }
        if (prevAngle.z != angle.z)
        {
            float deltaAngle = angle.z - prevAngle.z;
            rotation = glm::rotate(rotation, glm::radians(deltaAngle), glm::vec3(0, 0, 1));
            prevAngle = angle;
        }

        shader->setUniform(SE::MAT4F, "u_rotation", (void*)&rotation);

        // Translation:
        glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(position, 0.0f));

        shader->setUniform(SE::MAT4F, "u_translation", (void*)&translation);

        renderer.clear(0.2f, 0.2f, 0.2f);

        // Starting imgui frame:
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("##");

            ImGui::SliderFloat("Mix value", &mixValue, 0, 1);
            ImGui::SliderFloat2("Position", &position.x, -5, 5);
            ImGui::SliderFloat("Size", &size, 0, 1);
            ImGui::SliderFloat3("Rotation", &angle.x, -360, 360);

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
        
    }
    void processMouseMovement(float xoffset, float yoffset) override
    {
        
    }
    void processScroll(float offset) override
    {

    }

    std::unique_ptr<SE::VertexBuffer> vb;
    std::unique_ptr<SE::VertexArray> va;
    std::unique_ptr<SE::Shader> shader;
    std::unique_ptr<SE::Texture> texture1;
    std::unique_ptr<SE::Texture> texture2;
};

int main()
{
    App app;
    app.update();
}