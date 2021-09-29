//
// Created by quantum on 6/11/21.
//



#include "Application.h"
#include "Renderer/Renderer.h"


namespace Clay
{

   Application *Application::s_Instance = nullptr;

   Application::Application(const std::string& name)
   {
      CLAY_PROFILE_FUNCTION();
      s_Instance = this;

      _window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
      _window->SetEventCallback(BIND_EVENT_CB(Application::OnEvent));

      Renderer::Init();

      _imguiLayer = new ImGuiLayer();
      PushOverlay(_imguiLayer);
   }

   Application::~Application()
   {
      CLAY_PROFILE_FUNCTION();
      Renderer::Shutdown();
   }

   void Application::OnEvent(Event& e)
   {
      CLAY_PROFILE_FUNCTION();
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CB(Application::OnWindowClose));
      dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CB(Application::OnWindowResize));

//      CLAY_LOG_INFO("{0}", e.toString());
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


   bool Application::OnWindowResize(WindowResizeEvent& e)
   {
      CLAY_PROFILE_FUNCTION();
      if(e.GetWidth() == 0 || e.GetHeight() == 0)
      {
         _minimized = true;
         return false;
      }
      _minimized = false;
      Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

      return false;
   }

   void Application::Run()
   {
      CLAY_PROFILE_FUNCTION();
      _running = true;
      while (_running)
      {
         double time = glfwGetTime();
         Timestep timestep = time - _lastFrameTime;
         _lastFrameTime = time;

         if(!_minimized){
            {
               CLAY_PROFILE_SCOPE("Application::Run::LayerUpdate");
               for (Layer *layer : _layerStack)
                  layer->OnUpdate(timestep);
            }

            {
               CLAY_PROFILE_SCOPE("Application::Run::ImGuiRendering");
               // ImGui Rendering
               _imguiLayer->Begin();
               for (Layer *layer : _layerStack)
                  layer->OnImGuiRender();
               _imguiLayer->End();
            }
         }


         _window->OnUpdate();
      }
   }

   void Application::PushLayer(Layer *layer)
   {
      CLAY_PROFILE_FUNCTION();
      _layerStack.PushLayer(layer);
      layer->OnAttach();
   }

   void Application::PushOverlay(Layer *layer)
   {
      CLAY_PROFILE_FUNCTION();
      _layerStack.PushOverlay(layer);
      layer->OnAttach();
   }

   void Application::Close()
   {
      _running = false;
   }
}


