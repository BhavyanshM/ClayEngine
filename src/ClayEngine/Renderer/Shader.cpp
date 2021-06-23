//
// Created by quantum on 6/16/21.
//


#include "Shader.h"
#include "Platforms/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace Clay
{
   Shader *Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
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
            return new OpenGLShader(vertexSrc, fragmentSrc);
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI. ");
      return nullptr;
   }
}