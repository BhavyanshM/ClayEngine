#include "ImGuiMenu.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "Scene/Mesh/MeshTools.h"
#include "FileBrowserUI.h"

namespace Clay
{
    void ImGuiMenu::MeshPrimitiveOptions(std::vector<Ref<Model>>& _models)
    {
        ImGui::Begin("Mesh Primitives");
        ImGui::Text("Models: %d", _models.size());

        Ref<TriangleMesh> modelMesh;
        Ref<PointCloud> modelCloud;
        if(ImGui::Button("Add Cylinder"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::Cylinder(modelMesh, 20);
        }
        if(ImGui::Button("Add Sphere"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::Sphere(modelMesh, 0.1f, 80, 80);
        }
        if(ImGui::Button("Add Surface"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::Surface(modelMesh, 20, 20);
        }
        if(ImGui::Button("Add Cuboid"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::Cuboid(modelMesh, 0.1f, 0.2f, 0.3f);
        }
        if(ImGui::Button("Torus"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::Torus(modelMesh, 0.1, 0.2, 40, 40);
        }
        if(ImGui::Button("Add OBJ"))
        {
            modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
            MeshTools::LoadOBJ(modelMesh, ASSETS_PATH + std::string("Meshes/bunny-small.obj"));
        }
       if(ImGui::Button("Add OFF"))
       {
          modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
          MeshTools::LoadOFF(modelMesh, ASSETS_PATH + std::string("Meshes/car.off"));
//          modelMesh->Print();
       }
       if(ImGui::Button("Load OFF Vertices"))
       {
          modelCloud = std::make_shared<PointCloud>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
          modelCloud->LoadOFFVertices(ASSETS_PATH + std::string("Meshes/car.off"));
          //          modelMesh->Print();
       }
       if(ImGui::Button("Add Axes"))
       {
          modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.6,0.4,0.3,1.0), nullptr);
          MeshTools::CoordinateAxes(modelMesh);
          //          modelMesh->Print();
       }
        if(ImGui::Button("Clear All Primitives"))
        {
            if(_models.size() > 0)
            {
                CLAY_LOG_INFO("Models Found: {}", _models.size());
                _models.clear();
            }
        }
        if(modelMesh != nullptr)_models.push_back(std::move(std::dynamic_pointer_cast<Model>(modelMesh)));
        if(modelCloud != nullptr)_models.push_back(std::move(std::dynamic_pointer_cast<Model>(modelCloud)));
        ImGui::End();
    }

    void ImGuiMenu::RendererOptions()
    {
         /* Renderer ImGui Stats and Settings */
         ImGui::Begin("Renderer");

         auto triangleStats = Renderer::GetTriangleStats();
         ImGui::Text("Triangle Stats:");
         ImGui::Text("Draw Calls: %d", triangleStats.GetTotalDrawCallCount());
         ImGui::Text("Vertices: %d", triangleStats.GetTotalVertexCount());
         ImGui::Text("Triangle Count: %d", triangleStats.GetTotalTriangleCount());
         ImGui::Text("Indices: %d", triangleStats.GetTotalIndexCount());
         ImGui::NewLine();

         auto pointStats = Renderer::GetPointStats();
         ImGui::Text("Point Stats:");
         ImGui::Text("Draw Calls: %d", pointStats.GetTotalDrawCallCount());
         ImGui::Text("Vertices: %d", pointStats.GetTotalVertexCount());
         ImGui::Text("Line Count: %d", pointStats.GetTotalTriangleCount());
         ImGui::Text("Indices: %d", pointStats.GetTotalIndexCount());
         ImGui::NewLine();

         auto lineStats = Renderer::GetLlineStats();
         ImGui::Text("Line Stats:");
         ImGui::Text("Draw Calls: %d", lineStats.GetTotalDrawCallCount());
         ImGui::Text("Vertices: %d", lineStats.GetTotalVertexCount());
         ImGui::Text("Triangle Count: %d", lineStats.GetTotalTriangleCount());
         ImGui::Text("Indices: %d", lineStats.GetTotalIndexCount());
         ImGui::NewLine();

         ImGui::End();
    }

    void ImGuiMenu::FileBrowser()
    {
       ImGui::Begin("File Browser");
       FileBrowserUI::ImGuiUpdate();
       ImGui::End();
    }

}