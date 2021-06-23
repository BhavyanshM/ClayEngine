//
// Created by quantum on 6/16/21.
//

#ifndef CLAYENGINE_SHADER_H
#define CLAYENGINE_SHADER_H

#include "ClayHeaders.h"
#include "Log.h"

namespace Clay
{
   class Shader
   {
      public:
         virtual ~Shader() = default;

         virtual void Bind() const = 0;
         virtual void Unbind() const = 0;

         static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

   };
}

#endif //CLAYENGINE_SHADER_H
