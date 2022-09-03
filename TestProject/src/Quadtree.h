#pragma once

#include "SandboxEngine.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <memory>

struct BoundingSquare
{
    BoundingSquare(float scale, glm::vec3 originPos, glm::vec3 color)
    {
        float halfScale{ scale * 0.5f };
        float vertices[8 * 6] {
            originPos.x - halfScale , originPos.y - halfScale, originPos.z, color.r, color.g, color.b, // Bottom Left
            originPos.x - halfScale, originPos.y + halfScale, originPos.z, color.r, color.g, color.b, // Top Left

            originPos.x - halfScale, originPos.y + halfScale, originPos.z, color.r, color.g, color.b, // Top Left
            originPos.x + halfScale, originPos.y + halfScale, originPos.z, color.r, color.g, color.b, // Top Right

            originPos.x + halfScale, originPos.y + halfScale, originPos.z, color.r, color.g, color.b, // Top Right
            originPos.x + halfScale, originPos.y - halfScale, originPos.z, color.r, color.g, color.b, // Bottom Right

            originPos.x + halfScale, originPos.y - halfScale, originPos.z, color.r, color.g, color.b, // Bottom Right
            originPos.x - halfScale , originPos.y - halfScale, originPos.z, color.r, color.g, color.b, // Bottom Left
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
    ~BoundingSquare()
    {
        delete vb;
        vb = nullptr;
        delete va;
        va = nullptr;
    }
    SE::VertexBuffer* vb;
    SE::VertexArray* va;
};

enum QuadtreeIndex
{
    TopLeft = 0,    //00
    TopRight = 1,   //01
    BottomLeft = 2, //10
    BottomRight = 3 //11
    // NOTE: Left bit represents whether node is on top(0) or on bottom(1), and right bit represents whether it's left(0) or right(1)
};
struct Quadtree
{
    Quadtree(const float scale, const glm::vec3 position, const glm::vec3 color, unsigned int depth)
        : root(scale, position, color), depth(depth){}

    void Insert()
    {
        root.Subdivide(depth);
    }

    struct Node
    {
        Node(const float scale, const glm::vec3 position, const glm::vec3 color)
            : scale(scale), position(position), color(color), bs(scale, position, color) {}

        void Subdivide(unsigned int depth)
        {
            if (depth > 0)
            {
                if (this->childNodes == nullptr)
                {
                    // Initializing childNodes:
                    this->childNodes = new Node* [8];
                    for (int i{}; i < 8; ++i)
                    {
                        // Getting position:
                        glm::vec3 childPos = this->position;
                        if ((i & 2) == 2) childPos.y -= this->scale * 0.25f; // If on bottom
                        else              childPos.y += this->scale * 0.25f; // If on top

                        if ((i & 1) == 1) childPos.x += this->scale * 0.25f; // If on right
                        else              childPos.x -= this->scale * 0.25f; // If on left

                        childPos.z = this->position.z - 0.2;

                        // Getting color:
                        glm::vec3 childColor{
                            this->color.r - 0.3,
                            this->color.g - 0.3,
                            this->color.b - 0.3,
                        };

                        childNodes[i] = new Node(this->scale * 0.5f, childPos, childColor);
                    }
                }

                /*for (int i{}; i < 8; ++i)
                {
                    this->childNodes[i]->Subdivide(depth - 1);
                }*/
                this->childNodes[BottomLeft]->Subdivide(depth - 1);

            }

        }

        float scale;
        glm::vec3 position;
        glm::vec3 color;
        BoundingSquare bs;
        Node** childNodes{ nullptr };
    };

    unsigned int depth;
    Node root;
};

class QuadtreeApp : public SE::Application
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

    QuadtreeApp()
        : Application("QuadtreeApp", 1920, 1080)
    {
        quadtree.Insert();
        
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

    ~QuadtreeApp()
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
                ImGui::Text("Render calls per frame: %i", renderer.callCount);
                ImGui::Text("Camera:");
                ImGui::Text("   Press 'C' to toggle camera mode");
                ImGui::Text("   Scroll to adjust speed");
                ImGui::Text("   Speed: %i", (int)camera.speed);
                ImGui::End();
            }
            ImGui::Render();
        }

        renderer.callCount = 0;

        // Transforming & Rendering:
        {
            // Translation:
            glm::mat4 view = camera.getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), (float)window.width / (float)window.height, 0.1f, 1000.0f);
            glm::mat4 model(1.0f);
            glm::mat4 mvp = projection * view * model;
            shader->setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);
        }

        DrawNodes(quadtree.root);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DrawNodes(Quadtree::Node& node)
    {
        if (node.childNodes != nullptr)
        {
            for (int i{}; i < 8; ++i)
            {
                DrawNodes(*node.childNodes[i]);
            }
        }
        renderer.draw(*node.bs.va, 8, *shader.get(), SE::DrawMode::LINES);
    }
    void DebugDrawNodes(Quadtree::Node& node, unsigned int depth)
    {
        std::cerr << "Depth: " << depth << "\tScale: " << node.scale << "\tX: " << node.position.x << " Y: " << node.position.x << std::endl;

        if (node.childNodes != nullptr)
        {
            for (int i{}; i < 8; ++i)
            {
                DebugDrawNodes(*node.childNodes[i], depth - 1);
            }
        }
        renderer.draw(*node.bs.va, 8, *shader.get(), SE::DrawMode::LINES);
    }


    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.vert", "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.frag" } };

    bool cameraMode{ false };
    SE::Camera camera{ glm::vec3(0, 0, 20), 10.0f };
    Quadtree quadtree{ 10.0f, {0.0f, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f}, 3 };
};
