//
// Created by quantum on 6/11/21.
//

#include "Application.h"

namespace Clay
{

#define BIND_EVENT_CB(x) std::bind(&Application::x, this, std::placeholders::_1)

   Application::Application()
   {
      _window = std::unique_ptr<Window>(Window::Create());
      _window->SetEventCallback(BIND_EVENT_CB(OnEvent));
   }

   Application::~Application()
   {
   }

   void Application::OnEvent(Event& e)
   {
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CB(OnWindowClose));

      CLAY_LOG_TRACE("{0}", e.toString());
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
         _window->OnUpdate();
      }
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
