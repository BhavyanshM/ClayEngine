//
// Created by quantum on 6/18/21.
//

#include "VertexArray.h"
#include "Platforms/OpenGL/OpenGLVertexArray.h"


namespace Clay
{
   VertexArray *VertexArray::Create()
   {
      switch (Renderer::GetAPI())
      {
         case RenderAPI::None:
         {
            CLAY_LOG_INFO("Renderer API is None.");
            return nullptr;
         }
         case RenderAPI::OpenGL:
         {
            return new OpenGLVertexArray();
         }
      }
      CLAY_LOG_INFO("Could not find RenderAPI. ");
      return nullptr;
   }
}