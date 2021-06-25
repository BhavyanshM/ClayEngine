#include "Platforms/OpenGL/OpenGLFrameBuffer.h"
#include "Renderer.h"

namespace Clay
{
   Ref<FrameBuffer> FrameBuffer::Create(const FramebufferSpecification& spec)
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
            return std::make_shared<OpenGLFrameBuffer>(spec);
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI::API. ");
      return nullptr;
   }

}