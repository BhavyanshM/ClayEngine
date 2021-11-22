#include "ImGuiMenu.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "Scene/Mesh/MeshTools.h"

namespace Clay
{
    void ImGuiMenu::MeshPrimitiveOptions(std::vector<Ref<Model>>& _models)
    {
        ImGui::Begin("Mesh Primitives");
        ImGui::Text("ImGuiMenu Here");

        Ref<TriangleMesh> modelMesh;
        if(ImGui::Button("Add Cylinder"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::Cylinder(modelMesh, 20);
        }
        if(ImGui::Button("Add Sphere"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::Sphere(modelMesh, 0.1f, 20, 20);
        }
        if(ImGui::Button("Add Surface"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::Surface(modelMesh, 20, 20);
        }
        if(ImGui::Button("Add OBJ"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            modelMesh->LoadOBJ(ASSETS_PATH + std::string("Meshes/bunny-small.obj"));
        }
        if(modelMesh != nullptr)_models.emplace_back(std::dynamic_pointer_cast<Model>(modelMesh));
        ImGui::End();
    }

    void ImGuiMenu::RendererOptions()
    {
        /* Renderer ImGui Stats and Settings */
        ImGui::Begin("Renderer");
        auto stats = Renderer::GetTriangleStats();
        ImGui::Text("Renderer Stats:");
        ImGui::Text("Draw Calls: %d", stats.GetTotalDrawCallCount());
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Triangle Count: %d", stats.GetTotalTriangleCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
        ImGui::End();
    }
}