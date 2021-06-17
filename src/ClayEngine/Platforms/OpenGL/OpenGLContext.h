//
// Created by quantum on 6/16/21.
//

#ifndef CLAYENGINE_OPENGLCONTEXT_H
#define CLAYENGINE_OPENGLCONTEXT_H

#include "Core.h"
#include "Renderer/GraphicsContext.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace Clay
{
   class OpenGLContext : public GraphicsContext
   {
      public:
         OpenGLContext(GLFWwindow* windowHandle);

         virtual void Init() override;
         virtual void SwapBuffers() override;

      private:
         GLFWwindow* _windowHandle;
   };

}

#endif //CLAYENGINE_OPENGLCONTEXT_H
