//
// Created by quantum on 6/17/21.
//


#include "Renderer.h"
#include "VertexArray.h"

namespace Clay
{
   RenderAPI Renderer::s_RendererAPI = RenderAPI::OpenGL;

   void Renderer::BeginScene()
   {

   }

   void Renderer::EndScene()
   {
   }

   void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexBuffer)
   {
   }
}
