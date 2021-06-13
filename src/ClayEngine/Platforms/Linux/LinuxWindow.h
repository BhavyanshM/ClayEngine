//
// Created by quantum on 6/12/21.
//

#ifndef CLAYENGINE_LINUXWINDOW_H
#define CLAYENGINE_LINUXWINDOW_H

#include "Window.h"
#include "GLFW/glfw3.h"

namespace Clay
{
   class LinuxWindow : public Window
   {
      public:
         LinuxWindow(const WindowProps& props);
         virtual ~LinuxWindow();

         void OnUpdate() override;

         inline unsigned int GetWidth() const override {return _data.Width;}
         inline unsigned int GetHeight() const override {return _data.Height;}

         virtual void SetEventCallback(const EventCallbackFn& callback) override {_data.EventCallback = callback;}
         virtual void SetVSync(bool enabled) override;
         virtual bool IsVSync() const override;

      private:
         virtual void Init(const WindowProps& props);
         virtual void Shutdown();

      private:
         GLFWwindow* _Window;

         struct WindowData
         {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
         };

         WindowData _data;
   };

}

#endif //CLAYENGINE_LINUXWINDOW_H
