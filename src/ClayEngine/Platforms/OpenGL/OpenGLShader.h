//
// Created by quantum on 6/22/21.
//

#ifndef CLAYENGINE_OPENGLSHADER_H
#define CLAYENGINE_OPENGLSHADER_H

#include "Renderer/Shader.h"
#include "glm/glm.hpp"

namespace Clay
{
   class OpenGLShader : public Shader
   {
      public:
         OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
         ~OpenGLShader();

         virtual void Bind() const override;
         virtual void Unbind() const override;

         void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

      private:
         uint32_t _rendererId;
   };
}


#endif //CLAYENGINE_OPENGLSHADER_H
