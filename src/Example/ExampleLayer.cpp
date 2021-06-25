//
// Created by quantum on 6/20/21.
//

#include <glm/gtc/type_ptr.hpp>
#include "ExampleLayer.h"

ExampleLayer::ExampleLayer() : Clay::Layer("GameExample"), _cameraController(2000.0f / 2000.0f)
{
   _vertexArray = Clay::VertexArray::Create();

   float vertices[4 * 5] = {/* Position */  -0.5f, -0.5f, 0.0f,   /* TexCoord */ 0.0f, 0.0f,
         /* Position */  0.5f, -0.5f, 0.0f,    /* TexCoord */ 1.0f, 0.0f,
         /* Position */  0.5f, 0.5f, 0.0f,     /* TexCoord */ 1.0f, 1.0f,
         /* Position */  -0.5f, 0.5f, 0.0f,    /* TexCoord */ 0.0f, 1.0f};

   _vertexBuffer = Clay::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));

   Clay::BufferLayout layout = {{Clay::ShaderDataType::Float3, "a_Position"},
                                {Clay::ShaderDataType::Float2, "a_TexCoord"}};
   _vertexBuffer->SetLayout(layout);
   _vertexArray->AddVertexBuffer(_vertexBuffer);

   unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
   _indexBuffer = Clay::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

   _vertexArray->SetIndexBuffer(_indexBuffer);

   _shader = Clay::Shader::Create("/home/quantum/Workspace/FastStorage/IHMC_PhD/Research/ClayEngine/src/Example/Assets/Shaders/Texture.glsl");

   std::dynamic_pointer_cast<Clay::OpenGLShader>(_shader)->Bind();
   std::dynamic_pointer_cast<Clay::OpenGLShader>(_shader)->UploadUniformInt("u_Texture", 0);
};

void ExampleLayer::OnAttach()
{
   _texture = Clay::Texture2D::Create("/home/quantum/Workspace/FastStorage/IHMC_PhD/Research/ClayEngine/src/Example/Assets/Textures/Checkerboard.png");
//
//   Clay::FramebufferSpecification fbSpec;
//   fbSpec.width = 2000;
//   fbSpec.height = 2000;
//   _frameBuffer = Clay::FrameBuffer::Create(fbSpec);
}

void ExampleLayer::OnDetach()
{
   Layer::OnDetach();
}

void ExampleLayer::OnUpdate(Clay::Timestep ts)
{
   /* Camera Controller Abstraction Here. */
   _cameraController.OnUpdate(ts);

   /* Renderer handling from here. */
//   _frameBuffer->Bind();
   Clay::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
   Clay::RenderCommand::Clear();

   Clay::Renderer::BeginScene(_cameraController.GetCamera());

   _texture->Bind();

   Clay::Renderer::Submit(_shader, _vertexArray, glm::identity<glm::mat4>());

   Clay::Renderer::EndScene();
//   _frameBuffer->Unbind();
}

void ExampleLayer::OnImGuiRender()
{
//   static bool dockspaceOpen = true;
//   static bool opt_fullscreen = true;
//   static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
//
//   ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
//   if (opt_fullscreen)
//   {
//      const ImGuiViewport *viewport = ImGui::GetMainViewport();
//      ImGui::SetNextWindowPos(viewport->WorkPos);
//      ImGui::SetNextWindowSize(viewport->WorkSize);
//      ImGui::SetNextWindowViewport(viewport->ID);
//      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
//      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
//      window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
//      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
//   } else
//   {
//      dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
//   }
//
//   if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
//      window_flags |= ImGuiWindowFlags_NoBackground;
//
//   ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
//
//   if (opt_fullscreen)
//      ImGui::PopStyleVar(2);
//
//   // Submit the DockSpace
//   ImGuiIO& io = ImGui::GetIO();
//   if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
//   {
//      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
//      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
//   }
//
//   if (ImGui::BeginMenuBar())
//   {
//      if (ImGui::BeginMenu("File"))
//      {
//         if (ImGui::MenuItem("Exit"))
//            Clay::Application::Get().Close();
//
//         ImGui::EndMenu();
//      }
//      ImGui::EndMenuBar();
//   }
//
//   ImGui::Begin("Settings");
//   ImGui::Text("Renderer Stats:");
//   ImGui::ColorEdit4("Square Color", glm::value_ptr(_squareColor));
//
//   uint32_t textureId = _texture->GetRendererId();
//   ImGui::Image((void*)textureId, ImVec2{200,200} );
//   ImGui::End();
//
//   ImGui::End();
}

void ExampleLayer::OnEvent(Clay::Event& e)
{
   _cameraController.OnEvent(e);
}

