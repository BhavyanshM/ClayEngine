//
// Created by quantum on 6/20/21.
//

#include <glm/gtc/type_ptr.hpp>
#include "ExampleLayer.h"

ExampleLayer::ExampleLayer() : Clay::Layer("GameExample"), _cameraController(1000.0f / 1000.0f)
{
   _vertexArray = Clay::VertexArray::Create();

   float vertices[4 * 5] = {/* Position */  -0.5f, -0.5f, 0.0f,   /* TexCoord */ 0.0f, 0.0f,
         /* Position */  0.5f, -0.5f, 0.0f,    /* TexCoord */ 1.0f, 0.0f,
         /* Position */  0.5f, 0.5f, 0.0f,     /* TexCoord */ 1.0f, 1.0f,
         /* Position */  -0.5f, 0.5f, 0.0f,    /* TexCoord */ 0.0f, 1.0f};

   _vertexBuffer = Clay::VertexBuffer::Create(vertices, sizeof(vertices));

   Clay::BufferLayout layout = {{Clay::ShaderDataType::Float3, "a_Position"},
                                {Clay::ShaderDataType::Float2, "a_TexCoord"}};
   _vertexBuffer->SetLayout(layout);
   _vertexArray->AddVertexBuffer(_vertexBuffer);

   unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
   _indexBuffer = Clay::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

   _vertexArray->SetIndexBuffer(_indexBuffer);

   _shader = Clay::Shader::Create("/home/quantum/Workspace/Volume/CPP/ClayEngine/src/ClayEditor/Assets/Shaders/Texture.glsl");

   std::dynamic_pointer_cast<Clay::OpenGLShader>(_shader)->Bind();
   std::dynamic_pointer_cast<Clay::OpenGLShader>(_shader)->UploadUniformInt("u_Texture", 0);
};

void ExampleLayer::OnAttach()
{
   _texture = Clay::Texture2D::Create("/home/quantum/Workspace/Volume/CPP/ClayEngine/src/ClayEditor/Assets/Textures/Checkerboard.png");
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

}

void ExampleLayer::OnEvent(Clay::Event& e)
{
   _cameraController.OnEvent(e);

   if(e.GetEventType() == Clay::EventType::WindowResize)
   {
      auto& re = (Clay::WindowResizeEvent&)e;

//      float zoom = re.GetWidth() / 1000.0f
//
//      re.GetWidth(_cameraController.)
   }
}

