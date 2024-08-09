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
    BoundingSquare(float scale, glm::vec3 position, glm::vec3 color)
    {
        glm::vec3 originPos{ position };// For readability
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

struct Quadtree
{
    Quadtree(const float scale, const glm::vec3 position, const glm::vec3 color, unsigned int depth)
        : root(scale, position, color), depth(depth){}

    void Insert(const glm::vec3 point)
    {
        root.Subdivide(point, depth);
    }

    enum Index : unsigned int
    {
        TopLeft = 0b00,
        TopRight = 0b01,
        BottomLeft = 0b10,
        BottomRight = 0b11
        // NOTE: Left bit represents whether node is on top(0) or on bottom(1), and right bit represents whether it's left(0) or right(1)
    };

    struct Node
    {
        Node(const float scale, const glm::vec3 position, const glm::vec3 color)
            : scale(scale), position(position), color(color), bs(scale, position, color) {}

        void Subdivide(const glm::vec3 point, unsigned int depth)
        {
            if (depth > 0)
            {
                unsigned int childIndex{ GetPointIndex(point) };

                if (this->childNodes == nullptr)
                {
                    // Initializing childNodes:
                    this->childNodes = new Node* [4];
                    this->childNodes[TopLeft] = new Node{ this->scale * 0.5f, {
                        this->position.x - this->scale * 0.25f,
                        this->position.y + this->scale * 0.25f,
                        this->position.z }, this->color - 0.15f };
                    this->childNodes[TopRight] = new Node{ this->scale * 0.5f, {
                        this->position.x + this->scale * 0.25f,
                        this->position.y + this->scale * 0.25f,
                        this->position.z }, this->color - 0.15f };
                    this->childNodes[BottomLeft] = new Node{ this->scale * 0.5f, {
                        this->position.x - this->scale * 0.25f,
                        this->position.y - this->scale * 0.25f,
                        this->position.z }, this->color - 0.15f };
                    this->childNodes[BottomRight] = new Node{ this->scale * 0.5f, {
                        this->position.x + this->scale * 0.25f,
                        this->position.y - this->scale * 0.25f,
                        this->position.z }, this->color - 0.15f };

                }

                this->childNodes[childIndex]->Subdivide(point, depth - 1);

            }

        }

        // Gets index of the child node, in which given point is located
        unsigned int GetPointIndex(glm::vec3 point)
        {
            unsigned int index{ 0b00 };

            // Bottom or Top:
            index |= point.y > this->position.y ? 0b00 : 0b10;
            // Left or Right:
            index |= point.x < this->position.x ? 0b00 : 0b01;

            return index;
        }

        void DeleteChildNodes()
        {
            if (this->childNodes != nullptr)
            {
                for (int i{}; i < 4; ++i)
                {
                    this->childNodes[i]->DeleteChildNodes();
                }
                this->childNodes = nullptr;
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
        : Application("QuadtreeApp")
    {
        quadtree.Insert(point);
        
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
                ImGui::Text("Quadtree");
				int tmpdepth = depth;
                ImGui::SliderInt("Depth", &tmpdepth, 0, 10); // TODO: Remove crutch
				depth = tmpdepth;
                ImGui::Text("Point:");
                ImGui::SliderFloat2("Point", &point.x, -octreeScale / 2, octreeScale / 2);
                ImGui::SliderFloat2("Point1", &point1.x, -octreeScale / 2, octreeScale / 2);
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

        if (prevDepth != depth || prevPoint != point || prevPoint1 != point1)
        {
            quadtree.depth = depth;
            prevDepth = depth;

            prevPoint = point;
            prevPoint1 = point1;
            quadtree.root.DeleteChildNodes();
            quadtree.Insert(point);
            quadtree.Insert(point1);
        }

        DrawNodes(quadtree.root);
        DrawPoint(point, { 1.0f, 0.0f, 1.0f });
        DrawPoint(point1, { 0.0f, 1.0f, 0.0f });
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DrawNodes(Quadtree::Node& node)
    {
        if (node.childNodes != nullptr)
        {
            for (int i{}; i < 4; ++i)
            {
                DrawNodes(*node.childNodes[i]);
            }
        }
        renderer.draw(*node.bs.va, 8, *shader.get(), SE::DrawMode::LINES);
    }

    void DrawPoint(glm::vec3 point, glm::vec3 color)
    {
        float vertices[6]{
            point.x, point.y, point.z, color.r, color.g, color.b
        };
        SE::VertexBuffer vb{ vertices, sizeof(vertices), SE::BufferUsage::STATIC_DRAW };
        SE::VertexBufferLayout layout;
        SE::VertexAttribute positions{ 3, SE::FLOAT };
        SE::VertexAttribute colors{ 3, SE::FLOAT };
        layout.add(positions);
        layout.add(colors);
        SE::VertexArray va;
        va.add(vb, layout);
        renderer.draw(va, 1, *shader.get(), SE::DrawMode::POINTS);
    }

    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "../SandboxEngine/src/Graphics/shaders/primitive.vert", "../SandboxEngine/src/Graphics/shaders/primitive.frag" } };

    bool cameraMode{ false };
    SE::Camera camera{ glm::vec3(0, 0, 200), 10.0f };
    float octreeScale{ 100.0f };
    unsigned int depth{ 5 };
    unsigned int prevDepth{ depth };
    Quadtree quadtree{ octreeScale, {0.0f, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f}, depth };
    glm::vec3 point{ 0.0f, 0.0f, 0.0f };
    glm::vec3 prevPoint{ point };
    glm::vec3 point1{ 1.0f, 1.0f, 0.0f };
    glm::vec3 prevPoint1{ point };
};
