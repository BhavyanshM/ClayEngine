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

   _shader = Clay::Shader::Create("/home/quantum/Workspace/FastStorage/IHMC_PhD/Research/ClayEngine/src/Example/Assets/Shaders/FlatColor.glsl");


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

   Clay::Renderer::BeginScene(_cameraController.GetCamera());

   std::dynamic_pointer_cast<Clay::OpenGLShader>(_shader)->Bind();
   std::dynamic_pointer_cast<Clay::OpenGLShader>(_shader)->UploadUniformFloat4("u_Color", _squareColor);

   Clay::Renderer::Submit(_shader, _vertexArray, glm::identity<glm::mat4>());

   Clay::Renderer::EndScene();
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
