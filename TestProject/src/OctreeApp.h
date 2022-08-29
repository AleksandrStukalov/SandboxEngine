#pragma once

#include "SandboxEngine.h"

#include "SandboxEngine/Graphics/Primitives/BoundingBox.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <memory>
#include <vector>
#include <array>


enum OctreeIndices : unsigned int
{
    BottomLeftFront = 0,
    TopLeftFront = 1,
    TopRightFront = 2,
    BottomRightFront = 3,
    BottomLeftBack = 4,
    TopLeftBack = 5,
    TopRightBack = 6,
    BottomRightBack = 7
};
struct Octree
{
    Octree(const float scale, const glm::vec3 position)
        : root{ scale, position } {}

    struct Node
    {
        Node(const float scale = 1.0f, const glm::vec3 position = { 0.0f, 0.0f, 0.0f })
            : scale(scale), position(position) {}
        bool isLeaf()
        {
            return (
                childNodes[BottomLeftFront] == nullptr &&
                childNodes[TopLeftFront] == nullptr &&
                childNodes[TopRightFront] == nullptr &&
                childNodes[BottomRightFront] == nullptr &&
                childNodes[BottomLeftBack] == nullptr &&
                childNodes[TopLeftBack] == nullptr &&
                childNodes[TopRightBack] == nullptr &&
                childNodes[BottomRightBack] == nullptr
                );
        }

        float scale;
        glm::vec3 position;
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
    };


    void Subdivide(Node* node, const unsigned int depth)
    {
        for (int i{}; i < 8; ++i)
        {
            delete node->childNodes[i];
            node->childNodes[i] = nullptr;
        }

        if (depth > 0)
        {
            // Initializing given node's childNodes:
            node->childNodes[BottomLeftFront] = new Node(node->scale / 2, {
                    node->position.x - node->scale / 4,
                    node->position.y - node->scale / 4,
                    node->position.z + node->scale / 4,
                });
            node->childNodes[TopLeftFront] = new Node(node->scale / 2, {
                    node->position.x - node->scale / 4,
                    node->position.y + node->scale / 4,
                    node->position.z + node->scale / 4,
                });
            node->childNodes[TopRightFront] = new Node(node->scale / 2, {
                    node->position.x + node->scale / 4,
                    node->position.y + node->scale / 4,
                    node->position.z + node->scale / 4,
                });
            node->childNodes[BottomRightFront] = new Node(node->scale / 2, {
                    node->position.x + node->scale / 4,
                    node->position.y - node->scale / 4,
                    node->position.z + node->scale / 4,
                });
            node->childNodes[BottomLeftBack] = new Node(node->scale / 2, {
                    node->position.x - node->scale / 4,
                    node->position.y - node->scale / 4,
                    node->position.z - node->scale / 4,
                });
            node->childNodes[TopLeftBack] = new Node(node->scale / 2, {
                    node->position.x - node->scale / 4,
                    node->position.y + node->scale / 4,
                    node->position.z - node->scale / 4,
                });
            node->childNodes[TopRightBack] = new Node(node->scale / 2, {
                    node->position.x + node->scale / 4,
                    node->position.y + node->scale / 4,
                    node->position.z - node->scale / 4,
                });
            node->childNodes[BottomRightBack] = new Node(node->scale / 2, {
                    node->position.x + node->scale / 4,
                    node->position.y - node->scale / 4,
                    node->position.z - node->scale / 4,
                });

            for (int i{}; i < 8; ++i)
            {
                Subdivide(node->childNodes[i], depth - 1);
            }
        }

    }

    Node root;
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

        octree.Subdivide(&octree.root, depth);

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
                ImGui::SliderInt("Subdivision count", &depth, 0, 7);
                ImGui::End();
            }
            ImGui::Render();
        }

        // Transforming & Rendering:
        
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

        if (prevDepth != depth)
        {
            octree.Subdivide(&octree.root, depth);
            prevDepth = depth;
        }

        // Rendering:
        std::vector<BBVertex> vertices;
        //std::vector<unsigned int> indices;
        //unsigned int indexOffset{};
        unsigned int nodeCount{};
        getNodeMesh(octree.root, &vertices, &nodeCount);

        SE::VertexBuffer vb{ &vertices[0], (unsigned int)vertices.size() * 6 * sizeof(float), SE::BufferUsage::STATIC_DRAW };
        //SE::IndexBuffer ib{ &indices[0], SE::UNSIGNED_INT, (unsigned int)indices.size() * sizeof(unsigned int), SE::BufferUsage::STATIC_DRAW };
        SE::VertexBufferLayout layout;
        SE::VertexAttribute positions{ 3, SE::FLOAT };
        SE::VertexAttribute colors{ 3, SE::FLOAT };
        layout.add(positions);
        layout.add(colors);
        SE::VertexArray va;

        va.add(vb, layout);

        renderer.callCount = 0;
        renderer.draw(va, 48 *  nodeCount, *shader.get(), *atlas.get(), SE::DrawMode::LINES);
        

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    }

    struct BBVertex
    {
        glm::vec3 position;
        glm::vec3 color;
    };
    void getNodeMesh(Octree::Node& node, std::vector<BBVertex>* vertices, unsigned int* nodeCount)
    {
        glm::vec3 color;
        node.isLeaf() ? color = { 0.0f, 1.0f, 0.0f } : color = { 0.6f, 0.4f, 0.4f };

        // Adding bounding box to vb & ib
        glm::vec3 position{ node.scale / 2 + node.position.x, node.scale / 2 + node.position.y, node.scale / 2 + node.position.z };
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

        //// Indices
        //// Near
        //indices->push_back(*offset + 0);    indices->push_back(*offset + 1);
        //indices->push_back(*offset + 1);    indices->push_back(*offset + 2);
        //indices->push_back(*offset + 2);    indices->push_back(*offset + 3);
        //indices->push_back(*offset + 3);    indices->push_back(*offset + 0);
        //// Far
        //indices->push_back(*offset + 4);    indices->push_back(*offset + 5);
        //indices->push_back(*offset + 5);    indices->push_back(*offset + 6);
        //indices->push_back(*offset + 6);    indices->push_back(*offset + 7);
        //indices->push_back(*offset + 7);    indices->push_back(*offset + 6);
        //// Left
        //indices->push_back(*offset + 7);    indices->push_back(*offset + 6);
        //indices->push_back(*offset + 6);    indices->push_back(*offset + 1);
        //indices->push_back(*offset + 1);    indices->push_back(*offset + 0);
        //indices->push_back(*offset + 0);    indices->push_back(*offset + 7);
        //// Right
        //indices->push_back(*offset + 3);    indices->push_back(*offset + 2);
        //indices->push_back(*offset + 2);    indices->push_back(*offset + 5);
        //indices->push_back(*offset + 5);    indices->push_back(*offset + 4);
        //indices->push_back(*offset + 4);    indices->push_back(*offset + 3);
        //// Bottom
        //indices->push_back(*offset + 7);    indices->push_back(*offset + 0);
        //indices->push_back(*offset + 0);    indices->push_back(*offset + 3);
        //indices->push_back(*offset + 3);    indices->push_back(*offset + 4);
        //indices->push_back(*offset + 4);    indices->push_back(*offset + 7);
        //// Top
        //indices->push_back(*offset + 1);    indices->push_back(*offset + 6);
        //indices->push_back(*offset + 6);    indices->push_back(*offset + 5);
        //indices->push_back(*offset + 5);    indices->push_back(*offset + 2);
        //indices->push_back(*offset + 2);    indices->push_back(*offset + 1);
        //*offset += 8;

        if (!node.isLeaf())
        {
            for (int i{}; i < 8; ++i)
            {
                getNodeMesh(*node.childNodes[i], vertices, nodeCount);
            }
        }

    }
    //void drawNode(Octree::Node& node)
    //{
    //    std::vector<BBVertex> vertices;
    //    std::vector<unsigned int> indices;
    //    unsigned int indexOffset{};
    //    getNodeMesh(node, &vertices, &indices, &indexOffset);
    //
    //    SE::VertexBuffer vb{ &vertices[0], sizeof(vertices), SE::BufferUsage::STATIC_DRAW};
    //    SE::VertexBufferLayout layout;
    //    SE::VertexAttribute positions{ 3, SE::FLOAT };
    //    SE::VertexAttribute colors{ 3, SE::FLOAT };
    //    layout.add(positions);
    //    layout.add(colors);
    //    SE::VertexArray va;
    //
    //    va.add(vb, layout);
    //    SE::IndexBuffer ib{ &indices[0], SE::UNSIGNED_INT, sizeof(indices), SE::BufferUsage::STATIC_DRAW };
    //
    //    renderer.draw(va, ib, *shader.get(), *atlas.get(), SE::DrawMode::LINES);
    //}

    std::unique_ptr<SE::Camera> camera{ new SE::Camera(glm::vec3(0, 0, 5)) };
    std::unique_ptr<SE::Texture> atlas{ new SE::Texture{ "D:/Development/SandboxEngine/TestProject/resources/textures/atlas.png", true } };
    std::unique_ptr<SE::Shader> shader{ new SE::Shader{ "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.vert", "D:/Development/SandboxEngine/SandboxEngine/src/Graphics/shaders/primitive.frag" } };
    bool cameraMode{ false };
    float octreeScale{ 1.0f };
    glm::vec3 octreePosition{ 0.0f, 0.0f, 0.0f };
    int depth{ 0 };
    int prevDepth{ depth };
    Octree octree{ octreeScale, octreePosition };
};