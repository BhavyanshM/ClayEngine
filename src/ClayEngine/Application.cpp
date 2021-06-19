//
// Created by quantum on 6/11/21.
//



#include <glad/glad.h>
#include "Application.h"

namespace Clay
{

   Application *Application::s_Instance = nullptr;

   Application::Application()
   {
      s_Instance = this;

      _window = std::unique_ptr<Window>(Window::Create());
      _window->SetEventCallback(BIND_EVENT_CB(OnEvent));

      _imguiLayer = new ImGuiLayer();
      PushOverlay(_imguiLayer);

      _vertexArray.reset(VertexArray::Create());

      float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.2f, 0.1f, 1.0f};

      _vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));

      BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                             {ShaderDataType::Float4, "a_Color"}};
      _vertexBuffer->SetLayout(layout);

      _vertexArray->AddVertexBuffer(_vertexBuffer);

      unsigned int indices[3] = {0, 1, 2};
      _indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

      _vertexArray->SetIndexBuffer(_indexBuffer);

      std::string vertexSource = R"(
         #version 450 core

         layout(location = 0) in vec3 a_Position;
         layout(location = 1) in vec4 a_Color;

         out vec3 v_Position;
         out vec4 v_Color;

         void main(){
            gl_Position = vec4(a_Position, 1.0);
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

      _shader.reset(new Shader(vertexSource, fragmentSource));
   }

   Application::~Application()
   {
   }

   void Application::OnEvent(Event& e)
   {
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CB(OnWindowClose));

      CLAY_LOG_INFO("{0}", e.toString());

      for (auto it = _layerStack.end(); it != _layerStack.begin();)
      {
         (*--it)->OnEvent(e);
         if (e.IsHandled())
            break;
      }
   }

   bool Application::OnWindowClose(Event& e)
   {
      _running = false;
      return true;
   }

   void Application::Run()
   {
      while (_running)
      {
         glClearColor(0.1f, 0.1f, 0.1f, 1);
         glClear(GL_COLOR_BUFFER_BIT);

         RenderCommand::SetClearColor();
         RenderCommand::Clear();

         Renderer::BeginScene();

         _shader->Bind();
         Renderer::Submit(_vertexArray);

         Renderer::EndScene();

         _vertexArray->Bind();
         glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

         for (Layer *layer : _layerStack)
            layer->OnUpdate();

         // ImGui Rendering
         _imguiLayer->Begin();
         for (Layer *layer : _layerStack)
            layer->OnImGuiRender();
         _imguiLayer->End();

         _window->OnUpdate();
      }
   }

   void Application::PushLayer(Layer *layer)
   {
      _layerStack.PushLayer(layer);
      layer->OnAttach();
   }

   void Application::PushOverlay(Layer *layer)
   {
      _layerStack.PushOverlay(layer);
      layer->OnAttach();
   }
}

int main()
{
   Clay::Log::Init();
   CLAY_LOG_INFO("Welcome to Clay Engine!");

   Clay::Application app;
   app.Run();

   return 0;
}
