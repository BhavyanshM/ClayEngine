//
// Created by quantum on 6/29/21.
//
#include <glm/gtc/type_ptr.hpp>
#include "EditorLayer.h"
#include "Core/Timer.h"

#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include "unistd.h"
#include <boost/stacktrace.hpp>

namespace Clay
{
   void handler(int sig)
   {
      void *array[10];
      size_t size;
      size = backtrace(array, 10);
      fprintf(stderr, "Error: signal %d:\n", sig);
      backtrace_symbols_fd(array, size, STDERR_FILENO);
      std::cout << boost::stacktrace::stacktrace();
      exit(1);
   }

   EditorLayer::EditorLayer() : Layer("Sandbox2D"), _cameraController(1000.0f / 1000.0f)
   {
      signal(SIGSEGV, handler);
   }

   void EditorLayer::OnAttach()
   {
      CLAY_PROFILE_FUNCTION();
      _texture = Texture2D::Create("/home/quantum/Workspace/FastStorage/IHMC_PhD/Research/ClayEngine/src/ClayEditor/Assets/Textures/Checkerboard.png");

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
         _cameraController.OnUpdate(ts);

      Renderer2D::ResetStats();
      _frameBuffer->Bind();

      RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
      RenderCommand::Clear();

      Renderer2D::BeginScene(_cameraController.GetCamera());
      Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
      Renderer2D::DrawQuad({-0.5f, -0.5f}, {1.0f, 1.0f}, {0.2f, 0.5f, 0.3f, 1.0f});
      Renderer2D::DrawQuad({0.0f, 0.0f, -0.01f}, {2.0f, 2.0f}, _texture, 4.0f);

      for (float y = -4.0f; y < 4.0f; y += 0.1f)
      {
         for (float x = -4.0f; x < 4.0f; x += 0.1f)
         {
            glm::vec4 color = {(x + 4.0f) / 8.0f, 0.4f, (y + 4.0f) / 8.0f, 0.5f};
            Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
         }
      }
      Renderer2D::EndScene();
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
      auto stats = Renderer2D::GetStats();
      ImGui::Text("Renderer2D Stats:");
      ImGui::Text("Draw Calls: %d", stats.DrawCalls);
      ImGui::Text("Quad Count: %d", stats.QuadCount);
      ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
      ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
      ImGui::End();

      /* Viewport Region */
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});

      ImGui::Begin("Viewport");

      _viewportFocused = ImGui::IsWindowFocused();
      _viewportHovered = ImGui::IsWindowHovered();
      Application::Get().GetImGuiLayer()->BlockEvents(!_viewportFocused || !_viewportHovered);

      CLAY_LOG_INFO("Focused: {0}, Hovered: {1}", ImGui::IsWindowFocused(), ImGui::IsWindowHovered());

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