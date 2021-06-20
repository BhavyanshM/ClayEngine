//
// Created by quantum on 6/20/21.
//

#include "ExampleLayer.h"

ExampleLayer::ExampleLayer() : Clay::Layer("GameExample"), _camera(-1.0f, 1.0f, -1.0f, 1.0f), _cameraPosition(0.0f)
{
   _vertexArray.reset(Clay::VertexArray::Create());

   float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.2f, 0.1f, 1.0f};

   _vertexBuffer.reset(Clay::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));

   Clay::BufferLayout layout = {{Clay::ShaderDataType::Float3, "a_Position"},
                                {Clay::ShaderDataType::Float4, "a_Color"}};
   _vertexBuffer->SetLayout(layout);
   _vertexArray->AddVertexBuffer(_vertexBuffer);

   unsigned int indices[3] = {0, 1, 2};
   _indexBuffer.reset(Clay::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

   _vertexArray->SetIndexBuffer(_indexBuffer);

   std::string vertexSource = R"(
         #version 450 core

         layout(location = 0) in vec3 a_Position;
         layout(location = 1) in vec4 a_Color;

         uniform mat4 u_ViewProjection;

         out vec3 v_Position;
         out vec4 v_Color;

         void main(){
            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            v_Position = a_Position;
            v_Color = a_Color;
         }

      )";

   std::string fragmentSource = R"(
         #version 450 core

         layout(location = 0) out vec4 color;

         in vec3 v_Position;
         in vec4 v_Color;

         void main(){
            color = vec4(0.5 * v_Position + 0.5, 1.0);
            color = v_Color;
         }

      )";

   _shader.reset(new Clay::Shader(vertexSource, fragmentSource));
};

void ExampleLayer::OnUpdate()
{

   if(Clay::Input::IsKeyPressed(Clay::Key::LEFT))
      _cameraPosition.x -= _cameraSpeed;

   if(Clay::Input::IsKeyPressed(Clay::Key::RIGHT))
      _cameraPosition.x += _cameraSpeed;

   if(Clay::Input::IsKeyPressed(Clay::Key::UP))
      _cameraPosition.y += _cameraSpeed;

   if(Clay::Input::IsKeyPressed(Clay::Key::DOWN))
      _cameraPosition.y -= _cameraSpeed;

   if(Clay::Input::IsKeyPressed(Clay::Key::A))
      _cameraRotation += _cameraSpeed;

   if(Clay::Input::IsKeyPressed(Clay::Key::D))
      _cameraRotation -= _cameraSpeed;

   Clay::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
   Clay::RenderCommand::Clear();

   _camera.SetPosition(_cameraPosition);
   _camera.SetRotation(_cameraRotation);

   Clay::Renderer::BeginScene(_camera);

   Clay::Renderer::Submit(_shader, _vertexArray);

   Clay::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
   ImGui::Begin("Test");
   ImGui::Text("Game Application: Hello World!");
   ImGui::End();
}

void ExampleLayer::OnEvent(Clay::Event& e)
{
}

