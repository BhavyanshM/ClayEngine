//
// Created by quantum on 6/29/21.
//
#include <glm/gtc/type_ptr.hpp>
#include "Example2D.h"

Example2D::Example2D()
: Layer("Sandbox2D"), _cameraController(1000.0f / 1000.0f)
{
}

void Example2D::OnAttach()
{


}

void Example2D::OnDetach()
{
   Layer::OnDetach();
}

void Example2D::OnUpdate(Clay::Timestep ts)
{
   _cameraController.OnUpdate(ts);

   Clay::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
   Clay::RenderCommand::Clear();

   Clay::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
   Clay::Renderer2D::DrawQuad({-0.5f, -0.5f}, {1.0f, 1.0f}, {0.2f, 0.5f, 0.3f, 1.0f});


   Clay::Renderer2D::BeginScene(_cameraController.GetCamera());
   Clay::Renderer2D::EndScene();

}

void Example2D::OnEvent(Clay::Event& e)
{
   _cameraController.OnEvent(e);
}

void Example2D::OnImGuiRender()
{
   ImGui::Begin("Settings");
   ImGui::ColorEdit3("Square Color", glm::value_ptr(_squareColor));
   ImGui::End();
}
