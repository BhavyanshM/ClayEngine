//
// Created by quantum on 6/17/21.
//


#include "Renderer.h"
#include "VertexArray.h"

namespace Clay
{
   void Renderer::BeginScene()
   {

   }

   void Renderer::EndScene()
   {
   }

   void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
   {
      RenderCommand::DrawIndexed(vertexArray);
   }
}
