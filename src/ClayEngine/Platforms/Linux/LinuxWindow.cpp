//
// Created by quantum on 6/12/21.
//

#include "LinuxWindow.h"

namespace Clay
{
   static bool s_GLFWInitialized = false;

   Window* Window::Create(const WindowProps& props)
   {
      return new LinuxWindow(props);
   }

   LinuxWindow::LinuxWindow(const WindowProps& props)
   {
      Init(props);
   }

   LinuxWindow::~LinuxWindow()
   {
      Shutdown();
   }

   void LinuxWindow::Init(const WindowProps& props)
   {
      _data.Title = props.Title;
      _data.Height = props.Height;
      _data.Width = props.Width;

      CLAY_LOG_INFO("Creating Window: {0} ({1}, {2}) ", _data.Title, _data.Width, _data.Height);

      if(!s_GLFWInitialized)
      {
         int success = glfwInit();
         s_GLFWInitialized = true;
      }

      _Window = glfwCreateWindow((int)_data.Width, (int)_data.Height, _data.Title.c_str(), nullptr, nullptr);
      glfwMakeContextCurrent(_Window);
      glfwSetWindowUserPointer(_Window, &_data);
      SetVSync(true);
   }

   void LinuxWindow::OnUpdate()
   {
      glfwPollEvents();
      glfwSwapBuffers(_Window);
   }

   void LinuxWindow::SetVSync(bool enabled)
   {
      if(enabled)
         glfwSwapInterval(1);
      else
         glfwSwapInterval(1);

      _data.VSync = enabled;
   }

   bool LinuxWindow::IsVSync() const
   {
      return _data.VSync;
   }

   void LinuxWindow::Shutdown()
   {
      glfwDestroyWindow(_Window);
   }
}