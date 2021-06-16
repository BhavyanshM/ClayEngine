//
// Created by quantum on 6/11/21.
//

#include "Application.h"


namespace Clay
{

   Application* Application::s_Instance = nullptr;

   Application::Application()
   {
      s_Instance = this;

      _window = std::unique_ptr<Window>(Window::Create());
      _window->SetEventCallback(BIND_EVENT_CB(OnEvent));

      _imguiLayer = new ImGuiLayer();
      PushOverlay(_imguiLayer);

   }

   Application::~Application()
   {
   }

   void Application::OnEvent(Event& e)
   {
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CB(OnWindowClose));

      CLAY_LOG_INFO("{0}", e.toString());

      for(auto it = _layerStack.end(); it != _layerStack.begin(); )
      {
         (*--it)->OnEvent(e);
         if(e.IsHandled())
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
      while(_running)
      {
         glClearColor(1, 0, 1, 1);
         glClear(GL_COLOR_BUFFER_BIT);

         for(Layer* layer : _layerStack)
            layer->OnUpdate();

         // ImGui Rendering
         _imguiLayer->Begin();
         for(Layer* layer : _layerStack)
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
