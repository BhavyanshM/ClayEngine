//
// Created by quantum on 6/19/21.
//

#ifndef CLAYENGINE_RENDERCOMMAND_H
#define CLAYENGINE_RENDERCOMMAND_H

#include "Core/ClayHeaders.h"
#include "RendererAPI.h"

namespace Clay
{

   class RenderCommand
   {
      public:
         static void Init()
         {
            s_RendererAPI->Init();
         }

         inline static void SetClearColor(const glm::vec4& color)
         {
            s_RendererAPI->SetClearColor(color);
         }
         inline static void Clear()
         {
            s_RendererAPI->Clear();
         }
         inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
         {
            s_RendererAPI->SetViewPort(x,y, width, height);
         }

         inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
         {
            vertexArray->Bind();
            s_RendererAPI->DrawIndexed(vertexArray, indexCount);
         }

      private:
         static RendererAPI* s_RendererAPI;
   };
}


#endif //CLAYENGINE_RENDERCOMMAND_H
