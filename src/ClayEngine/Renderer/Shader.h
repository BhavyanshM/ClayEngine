//
// Created by quantum on 6/16/21.
//

#ifndef CLAYENGINE_SHADER_H
#define CLAYENGINE_SHADER_H


#include "glad/glad.h"
#include "vector"
#include "string"

#include "Log.h"

namespace Clay
{
   class Shader
   {
      public:
         Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
         ~Shader();

         void Bind();
         void Unbind();

      private:
         uint32_t _rendererId;
   };
}

#endif //CLAYENGINE_SHADER_H
