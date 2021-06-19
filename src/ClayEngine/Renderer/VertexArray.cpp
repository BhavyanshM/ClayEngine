//
// Created by quantum on 6/18/21.
//

#include "VertexArray.h"
#include "Platforms/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Clay
{
   VertexArray *VertexArray::Create()
   {
      switch (Renderer::GetAPI())
      {
         case RendererAPI::API::None:
         {
            CLAY_LOG_INFO("Renderer API is None.");
            return nullptr;
         }
         case RendererAPI::API::OpenGL:
         {
            return new OpenGLVertexArray();
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI. ");
      return nullptr;
   }
}