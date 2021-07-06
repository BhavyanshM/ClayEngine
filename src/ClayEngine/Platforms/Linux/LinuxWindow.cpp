//
// Created by quantum on 6/12/21.
//


#include "LinuxWindow.h"

namespace Clay
{
   static bool s_GLFWInitialized = false;

   Window *Window::Create(const WindowProps& props)
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

   void GLFWErrorCallback(int code, const char* description)
   {
      CLAY_LOG_ERROR("GLFW Error {(0)}: {1}", code, description);
   }

   void LinuxWindow::Init(const WindowProps& props)
   {
      CLAY_PROFILE_FUNCTION();
      _data.Title = props.Title;
      _data.Height = props.Height;
      _data.Width = props.Width;



      CLAY_LOG_INFO("Creating Window: {0} ({1}, {2}) ", _data.Title, _data.Width, _data.Height);

      if (!s_GLFWInitialized)
      {
         int success = glfwInit();
         s_GLFWInitialized = true;
         glfwSetErrorCallback(GLFWErrorCallback);
      }

      _window = glfwCreateWindow((int) _data.Width, (int) _data.Height, _data.Title.c_str(), nullptr, nullptr);
      _context = new OpenGLContext(_window);
      _context->Init();



      glfwSetWindowUserPointer(_window, &_data);
      SetVSync(true);

      glfwSetWindowSizeCallback(_window, [](GLFWwindow *window, int width, int height)
      {
         WindowData& data = *(WindowData *) glfwGetWindowUserPointer(window);
         data.Width = width;
         data.Height = height;

         WindowResizeEvent event(width, height);
         CLAY_LOG_INFO("Window Size: {0}, {1}", width, height);
         data.EventCallback(event);
      });

      glfwSetWindowCloseCallback(_window, [](GLFWwindow *window)
      {
         WindowData& data = *(WindowData *) glfwGetWindowUserPointer(window);
         WindowCloseEvent event;
         data.EventCallback(event);
      });

      glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int scanCode, int action, int mods)
      {
         WindowData& data = *(WindowData *) glfwGetWindowUserPointer(window);
         switch (action)
         {
            case GLFW_PRESS:
            {
               KeyPressedEvent event(key, 0);
               data.EventCallback(event);
               break;
            }
            case GLFW_RELEASE:
            {
               KeyReleasedEvent event(key);
               data.EventCallback(event);
               break;
            }
            case GLFW_REPEAT:
            {
               KeyPressedEvent event(key, 1);
               data.EventCallback(event);
               break;
            }
         }
      });

      glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods){
         WindowData& data = *(WindowData *) glfwGetWindowUserPointer(window);
         switch (action)
         {
            case GLFW_PRESS:
            {
               MouseButtonPressedEvent event(button);
               data.EventCallback(event);
               break;
            }
            case GLFW_RELEASE:
            {
               MouseButtonReleasedEvent event(button);
               data.EventCallback(event);
               break;
            }
         }
      });

      glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset){
         WindowData& data = *(WindowData *) glfwGetWindowUserPointer(window);
         MouseScrolledEvent event(xoffset, yoffset);
         data.EventCallback(event);
      });

      glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
         WindowData& data = *(WindowData *) glfwGetWindowUserPointer(window);
         MouseMovedEvent event(xpos, ypos);
         data.EventCallback(event);

      });
   }

   void LinuxWindow::OnUpdate()
   {
      CLAY_PROFILE_FUNCTION();
      glfwPollEvents();
      _context->SwapBuffers();

   }

   void LinuxWindow::SetVSync(bool enabled)
   {
      CLAY_PROFILE_FUNCTION();
      if (enabled)
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
      CLAY_PROFILE_FUNCTION();
      glfwDestroyWindow(_window);
   }
}