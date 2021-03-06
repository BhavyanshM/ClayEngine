//
// Created by quantum on 6/23/21.
//

#include "Texture.h"
#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLTexture.h"

namespace Clay
{
   Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
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
            return std::make_shared<OpenGLTexture2D>(width, height);
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI. ");
      return nullptr;
   }

   Ref<Texture2D> Texture2D::Create(const std::string& path)
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
            return std::make_shared<OpenGLTexture2D>(path);
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI. ");
      return nullptr;
   }

   Ref<Texture2D> Texture2D::Create()
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
            return std::make_shared<OpenGLTexture2D>();
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI. ");
      return nullptr;
   }

}