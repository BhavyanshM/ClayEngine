//
// Created by quantum on 6/16/21.
//

#include "OpenGLContext.h"

namespace Clay
{
   OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : _windowHandle(windowHandle)
   {
   }

   void OpenGLContext::Init()
   {
      CLAY_PROFILE_FUNCTION();
      glfwMakeContextCurrent(_windowHandle);
      int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
      CLAY_LOG_INFO("GLAD Initialization Code: {0}", status);

      CLAY_LOG_INFO("OpenGL Info: ");
      CLAY_LOG_INFO("{0}", glGetString(GL_VENDOR));
      CLAY_LOG_INFO("{0}", glGetString(GL_RENDERER));
      CLAY_LOG_INFO("{0}", glGetString(GL_VERSION));
   }

   void OpenGLContext::SwapBuffers()
   {
      CLAY_PROFILE_FUNCTION();
      glfwSwapBuffers(_windowHandle);
   }
}