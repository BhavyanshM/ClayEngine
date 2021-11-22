//
// Created by quantum on 6/29/21.
//
#include <Scene/Mesh/TriangleMesh.h>
#include "EditorLayer.h"
#include "Core/Timer.h"
#include "Scene/Mesh/MeshTools.h"


namespace Clay
{
   void handler(int sig)
   {
      void *array[1000];
      size_t size;
      size = backtrace(array, 1000);
      fprintf(stderr, "Error: signal %d:\n", sig);
      backtrace_symbols_fd(array, size, STDERR_FILENO);
      std::cout << boost::stacktrace::stacktrace();
      exit(1);
   }

   EditorLayer::EditorLayer() : Layer("Sandbox2D")
   {
      signal(SIGSEGV, handler);

      _rootPCL = std::make_shared<Model>();
      Ref<Model> cameraGrandParent = std::make_shared<Model>(_rootPCL);
      Ref<Model> cameraParent = std::make_shared<Model>(cameraGrandParent);
      Ref<Model> cameraModel = std::make_shared<Model>(cameraParent);
      _cameraController = CameraController(1000.0f / 1000.0f, cameraModel);

      Ref<TriangleMesh> modelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.3,0.5,0.7,1.0), _rootPCL);
      MeshTools::Cuboid(modelMesh, 0.1f, 0.2f, 0.05f);
//      modelMesh->LoadOBJ(ASSETS_PATH + std::string("Meshes/bunny-small.obj"));
      modelMesh->RotateLocalY(0.3f);
      modelMesh->TranslateLocal({0.2f, 0.3f, -0.5f});
      _models.emplace_back(std::dynamic_pointer_cast<Model>(modelMesh));

      Ref<TriangleMesh> modelMesh2 = std::make_shared<TriangleMesh>(glm::vec4(0.4,0.6,0.4,1.0), _rootPCL);
//      MeshTools::Cuboid(modelMesh2, 0.1f, 1.2f, 0.2f);
      modelMesh2->LoadOBJ(ASSETS_PATH + std::string("Meshes/bunny-small.obj"));
      modelMesh2->RotateLocalZ(-1.1f);
      modelMesh2->RotateLocalX(-0.21f);
      _models.emplace_back(std::dynamic_pointer_cast<Model>(modelMesh2));

//      modelMesh->Load(std::string(ASSETS_PATH) + "Meshes/Circle.pcd");
//      modelMesh->Print();

//      Ref<PointCloud> secondPCL = std::make_shared<PointCloud>(glm::vec4(0.3,0.8,0.3,1), _rootPCL);
//      secondPCL->Load(std::string(ASSETS_PATH) + "Meshes/OusterScan_02.pcd");

//      std::vector<int> partIds(secondPCL->GetSize(), 0);
//      for(int i = 0; i<partIds.size(); i++)
//      {
//         partIds[i] = i / 2000;
//      }
//      secondPCL->SetPartIds(partIds);
//      _models.emplace_back(std::dynamic_pointer_cast<Model>(secondPCL));
   }

   void EditorLayer::OnAttach()
   {
      CLAY_PROFILE_FUNCTION();

      _shader = Clay::Shader::Create(std::string(ASSETS_PATH) + std::string("Shaders/PointCloudShader.glsl"));
      _texture = Texture2D::Create(std::string(ASSETS_PATH) + std::string("Textures/Checkerboard.png"));

      FramebufferSpecification fbSpec;
      fbSpec.width = 1000;
      fbSpec.height = 1000;
      _frameBuffer = FrameBuffer::Create(fbSpec);
   }

   void EditorLayer::OnDetach()
   {
      CLAY_PROFILE_FUNCTION();
      Layer::OnDetach();
   }

   void EditorLayer::OnUpdate(Timestep ts)
   {
      CLAY_PROFILE_FUNCTION();

      if (_viewportFocused)
      {
         _cameraController.OnUpdate(ts);
      }

      Renderer::ResetStats();

      _frameBuffer->Bind();
      RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
      RenderCommand::Clear();

      Renderer::BeginScene(_cameraController.GetCamera());

      _rootPCL->Update();
      _currentTime += ts.GetMilliseconds() / 1000.0f;
      for(Ref<Model> model : _models)
      {
         Renderer::SubmitTriangles(model);
      }

      Renderer::EndScene();

      _frameBuffer->Unbind();
   }

   void EditorLayer::OnEvent(Event& e)
   {
      _cameraController.OnEvent(e);
   }

   void EditorLayer::OnImGuiRender()
   {
      CLAY_PROFILE_FUNCTION();

      static bool dockspaceOpen = true;
      static bool opt_fullscreen = true;
      static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

      ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
      if (opt_fullscreen)
      {
         const ImGuiViewport *viewport = ImGui::GetMainViewport();
         ImGui::SetNextWindowPos(viewport->WorkPos);
         ImGui::SetNextWindowSize(viewport->WorkSize);
         ImGui::SetNextWindowViewport(viewport->ID);
         ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
         ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
         window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
         window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
      } else
      {
         dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
      }

      if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
         window_flags |= ImGuiWindowFlags_NoBackground;

      ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);

      if (opt_fullscreen)
         ImGui::PopStyleVar(2);

      // Submit the DockSpace
      ImGuiIO& io = ImGui::GetIO();
      if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
      {
         ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
         ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
      }

      if (ImGui::BeginMenuBar())
      {
         if (ImGui::BeginMenu("File"))
         {
            if (ImGui::MenuItem("Exit"))
               Application::Get().Close();

            ImGui::EndMenu();
         }
         ImGui::EndMenuBar();
      }

      /* Renderer ImGui Stats and Settings */
      ImGui::Begin("Renderer");
      ImGui::ColorEdit3("Square Color", glm::value_ptr(_squareColor));
      auto stats = Renderer::GetTriangleStats();
      ImGui::Text("Renderer Stats:");
      ImGui::Text("Draw Calls: %d", stats.GetTotalDrawCallCount());
      ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
      ImGui::Text("Triangle Count: %d", stats.GetTotalTriangleCount());
      ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
      ImGui::End();

      /* Viewport Region */
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});

      ImGui::Begin("Viewport");

      _viewportFocused = ImGui::IsWindowFocused();
      _viewportHovered = ImGui::IsWindowHovered();
      Application::Get().GetImGuiLayer()->BlockEvents(!_viewportFocused || !_viewportHovered);

      ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

      if (_viewportSize != *((glm::vec2 *) &viewportPanelSize))
      {

         _viewportSize.x = viewportPanelSize.x;
         _viewportSize.y = viewportPanelSize.y;

         _frameBuffer->Resize((uint32_t) viewportPanelSize.x, (uint32_t) viewportPanelSize.y);
         _cameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
      }
      uint32_t textureId = _frameBuffer->GetColorAttachment();
      ImGui::Image((void *) textureId, ImVec2{_viewportSize.x, _viewportSize.y}, ImVec2{0, 1}, ImVec2(1, 0));
      ImGui::End();
      ImGui::PopStyleVar();

      ImGui::End();
   }
}