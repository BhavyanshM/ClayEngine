//
// Created by quantum on 6/16/21.
//


#include "Shader.h"
#include "Platforms/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace Clay
{
   Ref<Shader> Shader::Create(const std::string& filePath)
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
            return std::make_shared<OpenGLShader>(filePath);
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI. ");
      return nullptr;
   }

   Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
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
            return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
         }
      }
      CLAY_LOG_INFO("Could not find RendererAPI. ");
      return nullptr;
   }

   void ShaderLibrary::Add(const Ref<Shader>& shader)
   {
      auto& name = shader->GetName();
      _shaders[name] = shader;
   }

   void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
   {
      _shaders[name] = shader;
   }

   Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
   {
      auto shader = Shader::Create(filePath);
      Add(shader);
      return shader;
   }

   Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
   {
      auto shader = Shader::Create(filePath);
      Add(name, shader);
   }

   Ref<Shader> ShaderLibrary::Get(const std::string& name)
   {
      return Clay::Ref<Shader>();
   }
}