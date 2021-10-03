//
// Created by quantum on 6/22/21.
//

#ifndef CLAYENGINE_OPENGLSHADER_H
#define CLAYENGINE_OPENGLSHADER_H

#include "Core/ClayHeaders.h"
#include "Renderer/Shader.h"
#include "glm/glm.hpp"

// TODO: Remove this. This is not ideal.
typedef unsigned int GLenum;

namespace Clay
{
   class OpenGLShader : public Shader
   {
      public:
         OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
         OpenGLShader(const std::string& filePath);
         ~OpenGLShader();

         virtual void Bind() const override;
         virtual void Unbind() const override;

         virtual void SetInt(const std::string& name, int value) override;
         virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
         virtual void SetFloat(const std::string& name, float value) override;
         virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
         virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
         virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
         virtual void SetMat4Array(const std::string& name, const std::vector<glm::mat4>& values, uint32_t count) override;

         virtual const std::string& GetName() const override {return _name;};

         void UploadUniformInt(const std::string& name, int value);
         void UploadUniformFloat(const std::string& name, float value);
         void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
         void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
         void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
         void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
         void UploadUniformMat4Array(const std::string& name, const std::vector<glm::mat4>& values, uint32_t count);

         void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
         void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

      private:
         std::string ReadFile(const std::string& filePath);
         std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
         void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

      private:
         uint32_t _rendererId;
         std::string _name;
   };
}


#endif //CLAYENGINE_OPENGLSHADER_H
