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

    void Insert(glm::vec3 point)
    {
        root.Subdivide(point, depth);
    }

    enum Indices : unsigned int
    {
        BottomLeftFront = 0b000,
        BottomLeftBack = 0b001,
        BottomRightFront = 0b010,
        BottomRightBack = 0b011,
        TopLeftFront = 0b100,
        TopLeftBack = 0b101,
        TopRightFront = 0b110,
        TopRightBack = 0b111

        // NOTE: What each bit represents whether node is at the:
        // * Right bit -> front(0) or back(1)
        // * Middle bit -> left(0) or right(1)
        // * Left bit -> bottom(0) or top(1)
    };
    struct Node
    {
        Node(const float scale, const glm::vec3 position, const glm::vec3 color)
            : scale(scale), position(position), color(color), bb(scale, position, color) {}

        void Subdivide(glm::vec3 point, unsigned int depth)
        {
            if (depth > 0)
            {
                unsigned int childIndex{ GetPositionIndex(point) };

                if (this->childNodes == nullptr) 
                {
                    // Initializing childNodes:
                    this->childNodes = new Node* [8];
                    this->childNodes[BottomLeftFront] = new Node{ this->scale * 0.5f, {
                            this->position.x - this->scale * 0.25f,
                            this->position.y - this->scale * 0.25f,
                            this->position.z + this->scale * 0.25f,
                        }, this->color - 0.15f };
                    this->childNodes[BottomLeftBack] = new Node{ this->scale * 0.5f, {
                            this->position.x - this->scale * 0.25f,
                            this->position.y - this->scale * 0.25f,
                            this->position.z - this->scale * 0.25f,
                        }, this->color - 0.15f };
                    this->childNodes[BottomRightFront] = new Node{ this->scale * 0.5f, {
                            this->position.x + this->scale * 0.25f,
                            this->position.y - this->scale * 0.25f,
                            this->position.z + this->scale * 0.25f,
                        }, this->color - 0.15f };
                    this->childNodes[BottomRightBack] = new Node{ this->scale * 0.5f, {
                            this->position.x + this->scale * 0.25f,
                            this->position.y - this->scale * 0.25f,
                            this->position.z - this->scale * 0.25f,
                        }, this->color - 0.15f };
                    this->childNodes[TopLeftFront] = new Node{ this->scale * 0.5f, {
                            this->position.x - this->scale * 0.25f,
                            this->position.y + this->scale * 0.25f,
                            this->position.z + this->scale * 0.25f,
                        }, this->color - 0.15f };
                    this->childNodes[TopLeftBack] = new Node{ this->scale * 0.5f, {
                            this->position.x - this->scale * 0.25f,
                            this->position.y + this->scale * 0.25f,
                            this->position.z - this->scale * 0.25f,
                        }, this->color - 0.15f };
                    this->childNodes[TopRightFront] = new Node{ this->scale * 0.5f, {
                            this->position.x + this->scale * 0.25f,
                            this->position.y + this->scale * 0.25f,
                            this->position.z + this->scale * 0.25f,
                        }, this->color - 0.15f };
                    this->childNodes[TopRightBack] = new Node{ this->scale * 0.5f, {
                            this->position.x + this->scale * 0.25f,
                            this->position.y + this->scale * 0.25f,
                            this->position.z - this->scale * 0.25f,
                        }, this->color - 0.15f };
                }

                this->childNodes[childIndex]->Subdivide(point, depth - 1);
            }
        }
        // Gets index of the child node, in which given point is located
        unsigned int GetPositionIndex(glm::vec3 point)
        {
            unsigned int index{ 0b000 };

            // Front or Back:
            index |= point.z > this->position.z ? 0b000 : 0b001;
            // Left or Right:
            index |= point.x < this->position.x ? 0b000 : 0b010;
            // Bottom or Top:
            index |= point.y < this->position.y ? 0b000 : 0b100;

            return index;
        }

        void DeleteChildNodes()
        {
            if (this->childNodes != nullptr)
            {
                for (int i{}; i < 8; ++i)
                {
                    delete this->childNodes[i];
                    this->childNodes[i] = nullptr;
                }

                delete this->childNodes;
                this->childNodes = nullptr;
            }
        }

        float scale;
        glm::vec3 position;
        glm::vec3 color;
        BoundingBox bb;
        Node** childNodes{ nullptr };// Must be initialized with nullptr
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
        octree.Insert(point1);
        octree.Insert(point2);
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
                ImGui::Text("Octree:");
                int tmpdepth = octreeDepth;
                ImGui::SliderInt("Depth", &tmpdepth, 0, 10); // TODO: Remove crutch
				octreeDepth = tmpdepth;
                ImGui::Text("Points:");
                ImGui::SliderFloat3("Point1", &point1.x, -octreeScale * 0.5, octreeScale * 0.5);
                ImGui::SliderFloat3("Point2", &point2.x, -octreeScale * 0.5, octreeScale * 0.5);
                ImGui::End();
            }
            ImGui::Render();
        }

        // Transforming:
        {
            // Translation:
            glm::mat4 view = camera.getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), (float)window.width / (float)window.height, 0.1f, 1000.0f);
            glm::mat4 model(1.0f);
            glm::mat4 mvp = projection * view * model;
            shader->setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);
        }

        // Rendering:
        if (prevOctreeDepth != octreeDepth || prevPoint1 != point1 || prevPoint2 != point2)
        {
            octree.root.DeleteChildNodes();
            prevOctreeDepth = octreeDepth;
            octree.depth = octreeDepth;
            prevPoint1 = point1;
            octree.Insert(point1);
            prevPoint2 = point2;
            octree.Insert(point2);
        }

        DrawNodes(octree.root);
        DrawPoint(point1, { 0.5, 0.2, 0.7 });

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DrawNodes(Octree::Node& node)
    {
        if (node.childNodes != nullptr)
        {
            for (int i{}; i < 8; ++i)
            {
                DrawNodes(*node.childNodes[i]);
            }
        }
        renderer.draw(*node.bb.va, 48, *shader.get(), SE::DrawMode::LINES);
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

    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "SandboxEngine/src/Graphics/shaders/primitive.vert","SandboxEngine/src/Graphics/shaders/primitive.frag"}};
    bool cameraMode{ false };
    SE::Camera camera{ glm::vec3(0, 0, 20), 1.0f };
    
    float octreeScale{ 10.0f };
    unsigned int octreeDepth{ 5 };
    unsigned int prevOctreeDepth{ octreeDepth };
    Octree octree{ octreeScale, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, octreeDepth };

    glm::vec3 point1{ 1.0f, 1.0f, 1.0f };
    glm::vec3 prevPoint1{ point1 };

    glm::vec3 point2{ -1.0f, -1.0f, -1.0f };
    glm::vec3 prevPoint2{ point2 };
};
