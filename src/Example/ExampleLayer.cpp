//
// Created by quantum on 6/20/21.
//

#include "ExampleLayer.h"

ExampleLayer::ExampleLayer() : Clay::Layer("GameExample"), _camera(-1.0f, 1.0f, -1.0f, 1.0f), _cameraPosition(0.0f), _modelPosition(0.0f)
{
   _vertexArray.reset(Clay::VertexArray::Create());

   float vertices[4 * 5] = {/* Position */  -0.5f, -0.5f, 0.0f,   /* TexCoord */ 0.0f, 0.0f,
                            /* Position */  0.5f, -0.5f, 0.0f,    /* TexCoord */ 1.0f, 0.0f,
                            /* Position */  0.5f, 0.5f, 0.0f,     /* TexCoord */ 1.0f, 1.0f,
                            /* Position */  -0.5f, 0.5f, 0.0f,    /* TexCoord */ 0.0f, 1.0f
    };

   _vertexBuffer.reset(Clay::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));

   Clay::BufferLayout layout = {
         {Clay::ShaderDataType::Float3, "a_Position"},
         {Clay::ShaderDataType::Float2, "a_TexCoord"}
   };
   _vertexBuffer->SetLayout(layout);
   _vertexArray->AddVertexBuffer(_vertexBuffer);

   unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
   _indexBuffer.reset(Clay::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

   _vertexArray->SetIndexBuffer(_indexBuffer);

   std::string vertexSource = R"(
         #version 450 core

         layout(location = 0) in vec3 a_Position;
         layout(location = 1) in vec2 a_TexCoord;

         uniform mat4 u_ViewProjection;
         uniform mat4 u_Transform;

         out vec2 v_TexCoord;

         void main(){
            v_TexCoord = a_TexCoord;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
         }

      )";

   std::string fragmentSource = R"(
         #version 450 core

         layout(location = 0) out vec4 color;

         in vec2 v_TexCoord;

         uniform sampler2D u_Texture;

         void main(){
            color = texture(u_Texture, v_TexCoord);
         }

      )";

   _shader.reset(Clay::Shader::Create(vertexSource, fragmentSource));

   _texture = Clay::Texture2D::Create("/home/quantum/Workspace/FastStorage/IHMC_PhD/Research/ClayEngine/src/Example/Assets/Textures/Checkerboard.png");

   std::dynamic_pointer_cast<Clay::OpenGLShader>(_shader)->Bind();
   std::dynamic_pointer_cast<Clay::OpenGLShader>(_shader)->UploadUniformInt("u_Texture", 0);

};

void ExampleLayer::OnUpdate(Clay::Timestep ts)
{

   CLAY_LOG_INFO("Delta Time: {0} ({1})", ts.GetSeconds(), ts.GetMilliseconds());

   // Camera Transform Input
   if(Clay::Input::IsKeyPressed(Clay::Key::LEFT))
      _cameraPosition.x -= _cameraSpeed * ts;
   if(Clay::Input::IsKeyPressed(Clay::Key::RIGHT))
      _cameraPosition.x += _cameraSpeed * ts;
   if(Clay::Input::IsKeyPressed(Clay::Key::UP))
      _cameraPosition.y += _cameraSpeed * ts;
   if(Clay::Input::IsKeyPressed(Clay::Key::DOWN))
      _cameraPosition.y -= _cameraSpeed * ts;
   if(Clay::Input::IsKeyPressed(Clay::Key::A))
      _cameraRotation += _cameraSpeed * ts;
   if(Clay::Input::IsKeyPressed(Clay::Key::D))
      _cameraRotation -= _cameraSpeed * ts;

   // Model Transform Input
   if(Clay::Input::IsKeyPressed(Clay::Key::J))
      _modelPosition.x -= _modelSpeed * ts;
   if(Clay::Input::IsKeyPressed(Clay::Key::L))
      _modelPosition.x += _modelSpeed * ts;
   if(Clay::Input::IsKeyPressed(Clay::Key::I))
      _modelPosition.y += _modelSpeed * ts;
   if(Clay::Input::IsKeyPressed(Clay::Key::K))
      _modelPosition.y -= _modelSpeed * ts;

   Clay::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
   Clay::RenderCommand::Clear();

   _camera.SetPosition(_cameraPosition);
   _camera.SetRotation(_cameraRotation);

   Clay::Renderer::BeginScene(_camera);

   _texture->Bind();

   glm::mat4 transform = glm::translate(glm::mat4(1.0f), _modelPosition);
   Clay::Renderer::Submit(_shader, _vertexArray, transform);

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

