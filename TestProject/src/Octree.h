#pragma once

#include "SandboxEngine.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct BoundingBox
{
    BoundingBox(float scale, glm::vec3 position, glm::vec3 color)
    {
        glm::vec3 originPos{ position };// For readability
        float halfScale{ scale * 0.5f };
        float vertices[48 * 6] {
            // Front
            originPos.x - halfScale, originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Left Front
            originPos.x - halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Left Front

            originPos.x - halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Left Front
            originPos.x + halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Right Front

            originPos.x + halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Right Front
            originPos.x + halfScale, originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Right Front

            originPos.x + halfScale, originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Right Front
            originPos.x - halfScale , originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Left Front

            // Back
            originPos.x - halfScale , originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Left Back
            originPos.x - halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Left Back

            originPos.x - halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Left Back
            originPos.x + halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Right Back

            originPos.x + halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Right Back
            originPos.x + halfScale, originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Right Back

            originPos.x + halfScale, originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Right Back
            originPos.x - halfScale , originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Left Back

            // Left
            originPos.x - halfScale , originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Left Back
            originPos.x - halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Left Back

            originPos.x - halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Left Back
            originPos.x - halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Left Front

            originPos.x - halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Left Front
            originPos.x - halfScale , originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Left Front

            originPos.x - halfScale , originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Left Front
            originPos.x - halfScale , originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Left Back

            // Right
            originPos.x + halfScale, originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Right Front
            originPos.x + halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Right Front

            originPos.x + halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Right Front
            originPos.x + halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Right Back

            originPos.x + halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Right Back
            originPos.x + halfScale, originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Right Back

            originPos.x + halfScale, originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Right Back
            originPos.x + halfScale, originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Right Front
            
            // Bottom
            originPos.x - halfScale , originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Left Back
            originPos.x - halfScale , originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Left Front

            originPos.x - halfScale , originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Left Front
            originPos.x + halfScale, originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Right Front

            originPos.x + halfScale, originPos.y - halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Bottom Right Front
            originPos.x + halfScale, originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Right Back

            originPos.x + halfScale, originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Right Back
            originPos.x - halfScale , originPos.y - halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Bottom Left Back

            // Top
            originPos.x - halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Left Front
            originPos.x - halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Left Back

            originPos.x - halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Left Back
            originPos.x + halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Right Back

            originPos.x + halfScale, originPos.y + halfScale, originPos.z - halfScale, color.r, color.g, color.b, // Top Right Back
            originPos.x + halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Right Front

            originPos.x + halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Right Front
            originPos.x - halfScale, originPos.y + halfScale, originPos.z + halfScale, color.r, color.g, color.b, // Top Left Front
        };
        vb = new SE::VertexBuffer(vertices, sizeof(vertices), SE::BufferUsage::STATIC_DRAW);
        SE::VertexAttribute positions(3, SE::FLOAT);
        SE::VertexAttribute colors(3, SE::FLOAT);
        SE::VertexBufferLayout layout;
        layout.add(positions);
        layout.add(colors);
        va = new SE::VertexArray();
        va->add(*vb, layout);
    }
    ~BoundingBox()
    {
        delete vb;
        vb = nullptr;
        delete va;
        va = nullptr;
    }
    
    SE::VertexBuffer* vb;
    SE::VertexArray* va;
};

struct Octree
{
    Octree(const float scale, const glm::vec3 position, const glm::vec3 color, const unsigned int depth)
        : root(scale, position, color), depth(depth) {}
    
    enum Indices : unsigned int
    {
        BottomLeftFront = 0,     // 000
        BottomLeftBack = 1,      // 001
        BottomRightFront = 2,    // 010
        BottomRightBack = 3,     // 011
        TopLeftFront = 4,        // 100
        TopLeftBack = 5,         // 101
        TopRightFront = 6,       // 110
        TopRightBack = 7         // 111

        // NOTE: What each bit represents whether node is at the:
        // * Right bit -> front(0) or back(1)
        // * Middle bit -> left(0) or right(1)
        // * Left bit -> bottom(0) or top(1)

        // TODO: Try to make the same thing using values with 0b prefix
    };
    struct Node
    {
        Node(const float scale, const glm::vec3 position, const glm::vec3 color)
            : scale(scale), position(position), color(color), bb(scale, position, color) {}

        void Subdivide(unsigned int depth)
        {
            if (depth > 0)
            {
                if (this->childNodes == nullptr) {
                    // Initializing childNodes:
                    this->childNodes = new Node* [8];
                    for (int i{}; i < 8; ++i)
                    {
                        
                    }
                }
            }
        }

        float scale;
        glm::vec3 position;
        glm::vec3 color;
        BoundingBox bb;
        Node** childNodes;
    };

    Node root;
    unsigned int depth;
};

class OctreeApp : public SE::Application
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

    OctreeApp()
        : Application("OctreeApp", 1920, 1080)
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
        renderer.callCount = 0;

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
                ImGui::Text("Render calls per frame: %i", renderer.callCount);
                ImGui::Text("Camera:");
                ImGui::Text("   Press 'C' to toggle camera mode");
                ImGui::Text("   Scroll to adjust speed");
                ImGui::Text("   Speed: %i", (int)camera.speed);
                ImGui::End();
            }
            ImGui::Render();
        }

        // Transforming & Rendering:
        {
            // Translation:
            glm::mat4 view = camera.getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), (float)window.width / (float)window.height, 0.1f, 1000.0f);
            glm::mat4 model(1.0f);
            glm::mat4 mvp = projection * view * model;
            shader->setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);
        }

        BoundingBox bb{ 1.0f, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f} };
        renderer.draw(*bb.va, 48, *shader.get(), SE::DrawMode::LINES);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.vert", "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.frag" } };

    bool cameraMode{ false };
    SE::Camera camera{ glm::vec3(0, 0, 5), 1.0f };
};
