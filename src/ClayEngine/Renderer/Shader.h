//
// Created by quantum on 6/16/21.
//

#ifndef CLAYENGINE_SHADER_H
#define CLAYENGINE_SHADER_H

#include "Core/ClayHeaders.h"
#include "Core/Core.h"
#include "Core/Log.h"
#include "glm/glm.hpp"

namespace Clay
{
   class Shader
   {
      public:
         virtual ~Shader() = default;

         virtual void Bind() const = 0;
         virtual void Unbind() const = 0;

         virtual void SetInt(const std::string& name, int value) = 0;
         virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
         virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
         virtual void SetFloat(const std::string& name, float value) = 0;
         virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
         virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
         virtual void SetMat4Array(const std::string& name, const std::vector<glm::mat4>& values, uint32_t count) = 0;

         virtual const std::string& GetName() const = 0;

         static Ref<Shader> Create(const std::string& filePath);
         static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc);

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
