//
// Created by quantum on 6/19/21.
//

#ifndef CLAYENGINE_OPENGLRENDERERAPI_H
#define CLAYENGINE_OPENGLRENDERERAPI_H

#include <glad/glad.h>
#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"

namespace Clay
{
   class OpenGLRendererAPI : public RendererAPI
   {
      public:
         OpenGLRendererAPI();

         virtual void Init() override;

         virtual void SetClearColor(const glm::vec4& color) override;
         virtual void Clear() override;
         virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

         virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0, GLenum mode = GL_TRIANGLES) override;

         virtual void SetLineWidth(float width) override;
         virtual void SetPointSize(float size) override;
   };

}
#endif //CLAYENGINE_OPENGLRENDERERAPI_H
