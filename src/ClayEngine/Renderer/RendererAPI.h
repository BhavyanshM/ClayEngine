//
// Created by quantum on 6/19/21.
//

#ifndef CLAYENGINE_RENDERERAPI_H
#define CLAYENGINE_RENDERERAPI_H

#include "glm/glm.hpp"
#include "Renderer/VertexArray.h"

namespace Clay
{
   class RendererAPI
   {
      public:
         enum class API
         {
               None = 0, OpenGL = 1
         };

         virtual void SetClearColor(const glm::vec4& color) = 0;
         virtual void Clear() = 0;
         virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;


         inline static API GetAPI() {return s_API;}

      private:
         static API s_API;
   };
}

#endif //CLAYENGINE_RENDERERAPI_H
