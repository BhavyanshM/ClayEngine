//
// Created by quantum on 6/19/21.
//

#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Clay
{
   OpenGLRendererAPI::OpenGLRendererAPI()
   {
   }

   void OpenGLRendererAPI::Init()
   {
      CLAY_PROFILE_FUNCTION();

//#ifdef HZ_DEBUG
//      glEnable(GL_DEBUG_OUTPUT);
//		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
//
//		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
//#endif

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_PROGRAM_POINT_SIZE);

   }

   void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
   {
      glClearColor(color.r, color.g, color.b, color.a);
   }

   void OpenGLRendererAPI::Clear()
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }

   void OpenGLRendererAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
   {
      glViewport(x, y, width, height);
   }

   void OpenGLRendererAPI::SetPointSize(float size)
   {
      glPointSize(size);
   }

   void OpenGLRendererAPI::SetLineWidth(float width)
   {
      glLineWidth(width);
   }

   void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount, uint32_t mode)
   {
      vertexArray->Bind();
      uint32_t count = indexCount;
      switch(mode)
      {
         case RendererAPI::MODE::Points:
         {
            glDrawElements(GL_POINTS, count, GL_UNSIGNED_INT, nullptr);
            break;
         }
         case RendererAPI::MODE::Triangles:
         {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
            break;
         }
         case RendererAPI::MODE::Lines:
         {
//            CLAY_LOG_INFO("Count: {}", count);
            glDrawArrays(GL_LINES, 0, count);
            break;
         }
      }
      glBindTexture(GL_TEXTURE_2D, 0);
   }
}