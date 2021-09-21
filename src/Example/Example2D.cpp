//
// Created by quantum on 6/29/21.
//
#include <glm/gtc/type_ptr.hpp>
#include "Example2D.h"
#include "Core/Timer.h"

#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include "unistd.h"
#include <boost/stacktrace.hpp>

void handler(int sig) {
   void *array[10];
   size_t size;
   size = backtrace(array, 10);
   fprintf(stderr, "Error: signal %d:\n", sig);
   backtrace_symbols_fd(array, size, STDERR_FILENO);
   std::cout << boost::stacktrace::stacktrace();
   exit(1);
}

EditorLayer::EditorLayer()
: Layer("Sandbox2D"), _cameraController(1000.0f / 1000.0f)
{
   signal(SIGSEGV, handler);
}

void EditorLayer::OnAttach()
{
   CLAY_PROFILE_FUNCTION();
   _texture = Clay::Texture2D::Create(std::string(ASSETS_PATH) + std::string("Textures/Checkerboard.png"));
}

void EditorLayer::OnDetach()
{
   CLAY_PROFILE_FUNCTION();
   Layer::OnDetach();
}

void EditorLayer::OnUpdate(Clay::Timestep ts)
{
   CLAY_PROFILE_FUNCTION();

   _cameraController.OnUpdate(ts);

   Clay::Renderer2D::ResetStats();

   Clay::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
   Clay::RenderCommand::Clear();

   Clay::Renderer2D::BeginScene(_cameraController.GetCamera());
   Clay::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
   Clay::Renderer2D::DrawQuad({-0.5f, -0.5f}, {1.0f, 1.0f}, {0.2f, 0.5f, 0.3f, 1.0f});
   Clay::Renderer2D::DrawQuad({0.0f, 0.0f, -0.01f}, {2.0f, 2.0f}, _texture, 4.0f);

   for(float y = -4.0f; y < 4.0f; y += 0.1f)
   {
      for(float x = -4.0f; x < 4.0f; x += 0.1f)
      {
         glm::vec4 color = {(x + 4.0f) / 8.0f, 0.4f, (y + 4.0f) / 8.0f, 0.5f};
         Clay::Renderer2D::DrawQuad( {x, y}, {0.45f, 0.45f}, color);
      }
   }
   Clay::Renderer2D::EndScene();
}

void EditorLayer::OnEvent(Clay::Event& e)
{
   _cameraController.OnEvent(e);
}

void EditorLayer::OnImGuiRender()
{
   CLAY_PROFILE_FUNCTION();

   ImGui::Begin("Settings");

   auto stats = Clay::Renderer2D::GetStats();
   ImGui::Text("Renderer2D Stats:");
   ImGui::Text("Draw Calls: %d", stats.DrawCalls);
   ImGui::Text("Quad Count: %d", stats.QuadCount);
   ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
   ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

   ImGui::ColorEdit3("Square Color", glm::value_ptr(_squareColor));

   ImGui::End();
}
