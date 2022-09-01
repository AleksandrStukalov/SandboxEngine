#pragma once

#include "SandboxEngine.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <memory>
#include <vector>
#include <array>

struct BoundingBox
{
    BoundingBox(float scale, glm::vec3 position, glm::vec3 color)
    {
        glm::vec3 pos{ (scale * 0.5) + position.x, (scale * 0.5) + position.y, (scale * 0.5) + position.z };
        float vertices[48 * 6]{
            // Near
            -pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Left    // 0
            -pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Left       // 1

            -pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Left       // 1
            pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Right      // 2

            pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Right      // 2
            pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Right   // 3

            pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Right   // 3
            -pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Left    // 0

            // Far
            pos.x, -pos.y, -pos.z, color.r, color.g, color.b, // Far Bottom Left     // 4
            pos.x, pos.y, -pos.z, color.r, color.g, color.b, // Far Top Left        // 5

            pos.x, pos.y, -pos.z, color.r, color.g, color.b, // Far Top Left        // 5
            -pos.x, pos.y, -pos.z, color.r, color.g, color.b, // Far Top Right       // 6

            -pos.x, pos.y, -pos.z, color.r, color.g, color.b, // Far Top Right       // 6
            -pos.x, -pos.y, -pos.z, color.r, color.g, color.b,  // Far Bottom Right    // 7

            -pos.x, -pos.y, -pos.z, color.r, color.g, color.b,  // Far Bottom Right    // 7
            pos.x, -pos.y, -pos.z, color.r, color.g, color.b, // Far Bottom Left     // 4

            // Left
            -pos.x, -pos.y, -pos.z, color.r, color.g, color.b,  // Far Bottom Right    // 7
            -pos.x, pos.y, -pos.z, color.r, color.g, color.b,  // Far Top Right       // 6

            -pos.x, pos.y, -pos.z, color.r, color.g, color.b,  // Far Top Right       // 6
            -pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Left       // 1

            -pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Left       // 1
            -pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Left    // 0

            -pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Left    // 0
            -pos.x, -pos.y, -pos.z, color.r, color.g, color.b,  // Far Bottom Right    // 7
            
            // Right
            pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Right   // 3
            pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Right      // 2

            pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Right      // 2
            pos.x, pos.y, -pos.z, color.r, color.g, color.b, // Far Top Left        // 5

            pos.x, pos.y, -pos.z, color.r, color.g, color.b, // Far Top Left        // 5
            pos.x, -pos.y, -pos.z, color.r, color.g, color.b, // Far Bottom Left     // 4

            pos.x, -pos.y, -pos.z, color.r, color.g, color.b, // Far Bottom Left     // 4
            pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Right   // 3

            // Bottom
            -pos.x, -pos.y, -pos.z, color.r, color.g, color.b,  // Far Bottom Right    // 7
            -pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Left    // 0

            -pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Left    // 0
            pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Right   // 3
        
            pos.x, -pos.y, pos.z, color.r, color.g, color.b, // Near Bottom Right   // 3
            pos.x, -pos.y, -pos.z, color.r, color.g, color.b, // Far Bottom Left     // 4
            
            pos.x, -pos.y, -pos.z, color.r, color.g, color.b, // Far Bottom Left     // 4
            -pos.x, -pos.y, -pos.z, color.r, color.g, color.b,  // Far Bottom Right    // 7
        
            // Top
            -pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Left       // 1
            -pos.x, pos.y, -pos.z, color.r, color.g, color.b,  // Far Top Right       // 6
            
            -pos.x, pos.y, -pos.z, color.r, color.g, color.b,  // Far Top Right       // 6
            pos.x, pos.y, -pos.z, color.r, color.g, color.b, // Far Top Left        // 5
            
            pos.x, pos.y, -pos.z, color.r, color.g, color.b, // Far Top Left        // 5
            pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Right      // 2
            
            pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Right      // 2
            -pos.x, pos.y, pos.z, color.r, color.g, color.b, // Near Top Left       // 1
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

enum OctreeIndices : unsigned int
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
struct Octree
{
    Octree(const float scale, const glm::vec3 position, const glm::vec3 color, unsigned int depth)
        : root{ scale, position, color }, depth{ depth } {}

    void Insert(const glm::vec3 position)
    {
        root.Subdivide(position, this->depth);
    }

    struct Node
    {
        Node(const float scale, const glm::vec3 position, const glm::vec3 color)
            : scale(scale), position(position), color(color), bb(scale, position, color) {}

        bool IsLeaf()
        {
            return (
                childNodes[BottomLeftFront] == nullptr &&
                childNodes[BottomLeftBack] == nullptr &&
                childNodes[BottomRightFront] == nullptr &&
                childNodes[BottomRightBack] == nullptr &&
                childNodes[TopLeftFront] == nullptr &&
                childNodes[TopLeftBack] == nullptr &&
                childNodes[TopRightFront] == nullptr &&
                childNodes[TopRightBack] == nullptr
                );
        }

        void Subdivide(const glm::vec3 targetPosition, const unsigned int depth)
        {
            for (int i{}; i < 8; ++i)
            {
                delete this->childNodes[i];
                this->childNodes[i] = nullptr;
            }

            unsigned int childIndex{ GetChildIndex(targetPosition) };

            if (this->IsLeaf())
                {
                    // Initializing childNodes:
                childNodes[BottomLeftFront] = new Node(scale * 0.5, {
                        position.x - scale * 0.25,
                        position.y - scale * 0.25,
                        position.z + scale * 0.25 },
                        {
                        this->color.x + 0.1,
                        this->color.y + 0.1,
                        this->color.z + 0.1,
                        });
                    childNodes[BottomLeftBack] = new Node(scale * 0.5, {
                        position.x - scale * 0.25,
                        position.y - scale * 0.25,
                        position.z - scale * 0.25 },
                        {
                        this->color.x + 0.1,
                        this->color.y + 0.1,
                        this->color.z + 0.1,
                        });
                    childNodes[BottomRightFront] = new Node(scale * 0.5, {
                            position.x + scale * 0.25,
                            position.y - scale * 0.25,
                            position.z + scale * 0.25 },
                        {
                        this->color.x + 0.1,
                        this->color.y + 0.1,
                        this->color.z + 0.1,
                        });
                    childNodes[BottomRightBack] = new Node(scale * 0.5, {
                            position.x + scale * 0.25,
                            position.y - scale * 0.25,
                            position.z - scale * 0.25 },
                        {
                        this->color.x + 0.1,
                        this->color.y + 0.1,
                        this->color.z + 0.1,
                        });
                    childNodes[TopLeftFront] = new Node(scale * 0.5, {
                            position.x - scale * 0.25,
                            position.y + scale * 0.25,
                            position.z + scale * 0.25 },
                        {
                        this->color.x + 0.1,
                        this->color.y + 0.1,
                        this->color.z + 0.1,
                        });
                    childNodes[TopLeftBack] = new Node(scale * 0.5, {
                            position.x - scale * 0.25,
                            position.y + scale * 0.25,
                            position.z - scale * 0.25 },
                        {
                        this->color.x + 0.1,
                        this->color.y + 0.1,
                        this->color.z + 0.1,
                        });
                    childNodes[TopRightFront] = new Node(scale * 0.5, {
                            position.x + scale * 0.25,
                            position.y + scale * 0.25,
                            position.z + scale * 0.25 },
                        {
                        this->color.x + 0.1,
                        this->color.y + 0.1,
                        this->color.z + 0.1,
                        });
                    childNodes[TopRightBack] = new Node(scale * 0.5, {
                            position.x + scale * 0.25,
                            position.y + scale * 0.25,
                            position.z - scale * 0.25 },
                        {
                        this->color.x + 0.1,
                        this->color.y + 0.1,
                        this->color.z + 0.1,
                        });
                }

            if (depth > 0)
            {
                childNodes[childIndex]->Subdivide(targetPosition, depth - 1);
            }

        }

        // Gets index of the child node, in which given point is located
        unsigned int GetChildIndex(glm::vec3 targetPosition)
        {
            unsigned int index{ 0 };

            // Bottom or Top:
            index |= targetPosition.y < this->position.y ? 0 : 4/*0b001*/;
            // Left or Right:
            index |= targetPosition.x < this->position.x ? 0 : 2/*0b010*/;
            // Front or Back:
            index |= targetPosition.z > this->position.z ? 0 : 1/*0b100*/;

            return index;
        }

        float scale;
        glm::vec3 position;
        glm::vec3 color;
        Node* childNodes[8]{
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
        };
        BoundingBox bb;
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

    OctreeApp()
        : Application("OctreeApp", 1920, 1080)
    {
        camera->speed = 10.0f;
        
        octree.Insert(point);
        va.reset(getNodeVA(octree.root, &nodeCount));

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
                ImGui::Text("   Speed: %i", (int)camera->speed);
                ImGui::Text("Octree:");
                ImGui::SliderFloat("Scale", &octreeScale, 0, 10);
                ImGui::SliderFloat3("Position", &octreePosition.x, -10, 10);
                ImGui::Text("Point:");
                ImGui::SliderFloat3("Point", &point.x, -octreeScale, octreeScale);
                ImGui::End();
            }
            ImGui::Render();
        }
        
        // Transformation:
        {
            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera->FOV), (float)window.width / (float)window.height, 0.1f, 1000.0f);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(octreeScale));
            glm::mat4 translation = glm::translate(glm::mat4(1.0f), octreePosition);
            glm::mat4 model = translation * scale;
            glm::mat4 mvp = projection * view * model;
            shader->setUniform(SE::MAT4F, "u_transformation", (void*)&mvp);

        }

        if (prevPoint != point)
        {
            prevPoint = point;

            octree.Insert(point);
            va.reset(getNodeVA(octree.root, &nodeCount));
        }

        // Rendering:
        //DrawPoint(point);
        //renderer.draw(*va.get(), 48 * nodeCount, *shader.get(), *atlas.get(), SE::DrawMode::LINES);
        DrawNodes(octree.root);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    struct BBVertex
    {
        glm::vec3 position;
        glm::vec3 color;
    };
    void getNodeVertices(Octree::Node& node, std::vector<BBVertex>* vertices, unsigned int* nodeCount)
    {
        glm::vec3 color;
        //node.IsLeaf() ? color = { 0.0f, 1.0f, 0.0f } : color = { 0.6f, 0.4f, 0.4f };
        color = { ((*nodeCount) * 0.05),((*nodeCount) * 0.05),((*nodeCount) * 0.05)};

        // Adding bounding box to vb & ib
        glm::vec3 position{ node.scale * 0.5 + node.position.x, node.scale * 0.5 + node.position.y, node.scale * 0.5 + node.position.z };
        // Vertices
        // Near
        vertices->push_back({ { -position.x, -position.y, position.z }, color });   // 0
        vertices->push_back({ { -position.x, position.y, position.z }, color });    // 1

        vertices->push_back({ { -position.x, position.y, position.z }, color });    // 1
        vertices->push_back({ { position.x, position.y, position.z }, color });     // 2

        vertices->push_back({ { position.x, position.y, position.z }, color });     // 2
        vertices->push_back({ { position.x, -position.y, position.z }, color });    // 3

        vertices->push_back({ { position.x, -position.y, position.z }, color });    // 3
        vertices->push_back({ { -position.x, -position.y, position.z }, color });   // 0

        // Far
        vertices->push_back({ { position.x, -position.y, -position.z }, color });   // 4
        vertices->push_back({ { position.x, position.y, -position.z }, color });    // 5

        vertices->push_back({ { position.x, position.y, -position.z }, color });    // 5
        vertices->push_back({ { -position.x, position.y, -position.z }, color });   // 6

        vertices->push_back({ { -position.x, position.y, -position.z }, color });   // 6
        vertices->push_back({ { -position.x, -position.y, -position.z }, color });  // 7

        vertices->push_back({ { -position.x, -position.y, -position.z }, color });  // 7
        vertices->push_back({ { position.x, -position.y, -position.z }, color });   // 4

        // Left
        vertices->push_back({ { -position.x, -position.y, -position.z }, color });  // 7
        vertices->push_back({ { -position.x, position.y, -position.z }, color });   // 6

        vertices->push_back({ { -position.x, position.y, -position.z }, color });   // 6
        vertices->push_back({ { -position.x, position.y, position.z }, color });    // 1

        vertices->push_back({ { -position.x, position.y, position.z }, color });    // 1
        vertices->push_back({ { -position.x, -position.y, position.z }, color });   // 0

        vertices->push_back({ { -position.x, -position.y, position.z }, color });   // 0
        vertices->push_back({ { -position.x, -position.y, -position.z }, color });  // 7

        // Right
        vertices->push_back({ { position.x, -position.y, position.z }, color });    // 3
        vertices->push_back({ { position.x, position.y, position.z }, color });     // 2

        vertices->push_back({ { position.x, position.y, position.z }, color });     // 2
        vertices->push_back({ { position.x, position.y, -position.z }, color });    // 5

        vertices->push_back({ { position.x, position.y, -position.z }, color });    // 5
        vertices->push_back({ { position.x, -position.y, -position.z }, color });   // 4

        vertices->push_back({ { position.x, -position.y, -position.z }, color });   // 4
        vertices->push_back({ { position.x, -position.y, position.z }, color });    // 3

        // Bottom
        vertices->push_back({ { -position.x, -position.y, -position.z }, color });  // 7
        vertices->push_back({ { -position.x, -position.y, position.z }, color });   // 0

        vertices->push_back({ { -position.x, -position.y, position.z }, color });   // 0
        vertices->push_back({ { position.x, -position.y, position.z }, color });    // 3
        
        vertices->push_back({ { position.x, -position.y, position.z }, color });    // 3
        vertices->push_back({ { position.x, -position.y, -position.z }, color });   // 4

        vertices->push_back({ { position.x, -position.y, -position.z }, color });   // 4
        vertices->push_back({ { -position.x, -position.y, -position.z }, color });  // 7

        // Top
        vertices->push_back({ { -position.x, position.y, position.z }, color });    // 1
        vertices->push_back({ { -position.x, position.y, -position.z }, color });   // 6

        vertices->push_back({ { -position.x, position.y, -position.z }, color });   // 6
        vertices->push_back({ { position.x, position.y, -position.z }, color });    // 5

        vertices->push_back({ { position.x, position.y, -position.z }, color });    // 5
        vertices->push_back({ { position.x, position.y, position.z }, color });     // 2

        vertices->push_back({ { position.x, position.y, position.z }, color });     // 2
        vertices->push_back({ { -position.x, position.y, position.z }, color });    // 1

        ++(*nodeCount);

        for (int i{}; i < 8; ++i)
        {
            if (node.childNodes[i] != nullptr)
            {
                getNodeVertices(*node.childNodes[i], vertices, nodeCount);
            }
        }
        

    }
    SE::VertexArray* getNodeVA(Octree::Node& node, unsigned int* nodeCount)
    {
        std::vector<BBVertex> vertices;
        getNodeVertices(octree.root, &vertices, nodeCount);

        vb.reset(new SE::VertexBuffer{ &vertices[0], (unsigned int)vertices.size() * 6 * sizeof(float), SE::BufferUsage::STATIC_DRAW });
        SE::VertexBufferLayout layout;
        SE::VertexAttribute positions{ 3, SE::FLOAT };
        SE::VertexAttribute colors{ 3, SE::FLOAT };
        layout.add(positions);
        layout.add(colors);
        SE::VertexArray* vertexArray = new SE::VertexArray();

        vertexArray->add(*vb.get(), layout);

        return vertexArray;
    }
    void DrawPoint(glm::vec3 point)
    {
        glm::vec3 color{ 1.0f };
        float vertices[6]{
            point.x, point.y, point.z, color.x, color.y, color.z,
        };
        SE::VertexBuffer vertbuffer{ vertices, sizeof(vertices), SE::BufferUsage::STATIC_DRAW };
        SE::VertexBufferLayout layout;
        SE::VertexAttribute positions{ 3, SE::FLOAT };
        SE::VertexAttribute colors{ 3, SE::FLOAT };
        layout.add(positions);
        layout.add(colors);
        SE::VertexArray vertarray;
        vertarray.add(vertbuffer, layout);
        renderer.draw(vertarray, 1, *shader.get(), *atlas.get(), SE::DrawMode::POINTS);
    }
    void DrawNodes(Octree::Node& node)
    {
        if (!node.IsLeaf())
        {
            for (auto childNode : node.childNodes)
            {
                DrawNodes(*childNode);
            }
        }
        else
        {
            renderer.draw(*node.bb.va, 48, *shader.get(), *atlas.get(), SE::DrawMode::LINES);
        }
    }

    std::unique_ptr<SE::Camera> camera{ new SE::Camera(glm::vec3(0, 0, 5)) };
    std::unique_ptr<SE::Texture> atlas{ new SE::Texture{ "D:/Development/SandboxEngine/TestProject/resources/textures/atlas.png", true } };
    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.vert", "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.frag" } };
    bool cameraMode{ false };

    float octreeScale{ 1.0f };
    glm::vec3 octreePosition{ 0.0f, 0.0f, 0.0f };
    glm::vec3 octreeColor{ 0.1f, 0.2f, 0.3f };
    Octree octree{ octreeScale, octreePosition, octreeColor, 3 };
    std::unique_ptr<SE::VertexArray> va;
    std::unique_ptr<SE::VertexBuffer> vb;
    unsigned int nodeCount{ 0 };

    glm::vec3 point{ 0, 0, 0 };
    glm::vec3 prevPoint{ point };
};
