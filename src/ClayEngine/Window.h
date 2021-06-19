//
// Created by quantum on 6/12/21.
//

#ifndef CLAYENGINE_WINDOW_H
#define CLAYENGINE_WINDOW_H

#include "Core.h"
#include "Events/Event.h"
#include <functional>

namespace Clay
{
   struct WindowProps
   {
      std::string Title;
      unsigned int Width;
      unsigned int Height;

      WindowProps(std::string title = "Clay Engine Window",
                  unsigned int height = 1080,
                  unsigned int width = 1920) : Title(title), Height(height), Width(width) {}
   };

   class Window
   {
      public:
         using EventCallbackFn = std::function<void(Event&)>;

         virtual ~Window() {}
         virtual void OnUpdate() = 0;

         virtual unsigned int GetWidth() const = 0;
         virtual unsigned int GetHeight() const = 0;

         virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
         virtual void SetVSync(bool enabled) = 0;
         virtual bool IsVSync() const = 0;

         virtual void* GetNativeWindow() const = 0;

         static Window* Create(const WindowProps& props = WindowProps());
   };
}

#endif //CLAYENGINE_WINDOW_H
