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

         enum MODE
         {
               Triangles = 0, Points = 1, Lines = 2
         };

         virtual void Init() = 0;
         virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
         virtual void SetClearColor(const glm::vec4& color) = 0;
         virtual void Clear() = 0;

         virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0, unsigned int mode = 0) = 0;

         virtual void SetLineWidth(float width) = 0;
         virtual void SetPointSize(float size) = 0;

         inline static API GetAPI() {return s_API;}

      private:
         static API s_API;
   };
}

#endif //CLAYENGINE_RENDERERAPI_H
