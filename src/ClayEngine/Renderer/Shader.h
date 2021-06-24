//
// Created by quantum on 6/16/21.
//

#ifndef CLAYENGINE_SHADER_H
#define CLAYENGINE_SHADER_H

#include "ClayHeaders.h"
#include "Core.h"
#include "Log.h"

namespace Clay
{
   class Shader
   {
      public:
         virtual ~Shader() = default;

         virtual void Bind() const = 0;
         virtual void Unbind() const = 0;

         virtual const std::string& GetName() const = 0;

         static Ref<Shader> Create(const std::string& filePath);
         static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

   };

   class ShaderLibrary
   {
      public:
         void Add(const Ref<Shader>& shader);
         void Add(const std::string& name, const Ref<Shader>& shader);
         Ref<Shader> Load(const std::string& filePath);
         Ref<Shader> Load(const std::string& name, const std::string& filePath);
         Ref<Shader> Get(const std::string& name);

      private:
         std::unordered_map<std::string, Ref<Shader>> _shaders;
   };
}

#endif //CLAYENGINE_SHADER_H
