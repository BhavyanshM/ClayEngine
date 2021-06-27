//
// Created by quantum on 6/19/21.
//

#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Clay
{
   OpenGLRendererAPI::OpenGLRendererAPI()
   {
   }

   void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
   {
      glClearColor(color.r, color.g, color.b, color.a);
   }

   void OpenGLRendererAPI::Clear()
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }

   void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
   {
      glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
   }

   void OpenGLRendererAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
   {
      glViewport(x, y, width, height);
   }
}