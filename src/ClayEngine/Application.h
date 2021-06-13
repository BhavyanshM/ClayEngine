//
// Created by quantum on 6/11/21.
//

#ifndef CLAYENGINE_APPLICATION_H
#define CLAYENGINE_APPLICATION_H

#include "Log.h"
#include <iostream>
#include "GLFW/glfw3.h"

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

namespace Clay
{
   class Application
   {
      public:
         Application();

         virtual ~Application();

         void Run();

      private:
         std::unique_ptr<Window> _window;
         bool _running;
   };

   Application* CreateApplication();
}
#endif //CLAYENGINE_APPLICATION_H
