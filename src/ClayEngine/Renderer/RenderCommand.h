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
         inline static void SetClearColor(const glm::vec4& color)
         {
            s_RendererAPI->SetClearColor(color);
         }
         inline static void Clear()
         {
            s_RendererAPI->Clear();
         }
         inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
         {
            vertexArray->Bind();
            s_RendererAPI->DrawIndexed(vertexArray);
         }
      private:
         static RendererAPI* s_RendererAPI;
   };
}


#endif //CLAYENGINE_RENDERCOMMAND_H
