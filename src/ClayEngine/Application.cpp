//
// Created by quantum on 6/11/21.
//

#include "Application.h"

namespace Clay
{

   Application::Application()
   {
      _window = std::unique_ptr<Window>(Window::Create());
   }

   Application::~Application()
   {
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
