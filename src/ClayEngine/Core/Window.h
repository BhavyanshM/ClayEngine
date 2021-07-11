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
      uint32_t Width;
      uint32_t Height;

      WindowProps(std::string title = "Clay Engine Window",
                  uint32_t height = 1000,
                  uint32_t width = 1000) : Title(title), Height(height), Width(width) {}
   };

   class Window
   {
      public:
         using EventCallbackFn = std::function<void(Event&)>;

         virtual ~Window() {}
         virtual void OnUpdate() = 0;

         virtual uint32_t GetWidth() const = 0;
         virtual uint32_t GetHeight() const = 0;

         virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
         virtual void SetVSync(bool enabled) = 0;
         virtual bool IsVSync() const = 0;

         virtual void* GetNativeWindow() const = 0;

         static Window* Create(const WindowProps& props = WindowProps());
   };
}

#endif //CLAYENGINE_WINDOW_H
