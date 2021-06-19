//
// Created by quantum on 6/17/21.
//

#include "Buffer.h"
#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

namespace Clay
{
   VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size)
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
            return new OpenGLVertexBuffer(vertices, size);
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI::API. ");
      return nullptr;
   }

   IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size)
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
            return new OpenGLIndexBuffer(indices, size);
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI::API. ");
      return nullptr;
   }
}