//
// Created by quantum on 6/17/21.
//


#include "Renderer.h"
#include "Renderer2D.h"
#include "RenderCommand.h"
#include "VertexArray.h"


namespace Clay
{
   Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

   void Renderer::Init()
   {
      RenderCommand::Init();
      Renderer2D::Init();
   }

   void Renderer::Shutdown()
   {
      Renderer2D::Shutdown();
   }

   void Renderer::OnWindowResize(uint32_t width, uint32_t height)
   {
      RenderCommand::SetViewPort(0,0, width, height);
   }

   void Renderer::BeginScene(OrthographicCamera& camera)
   {
      s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
   }

   void Renderer::EndScene()
   {
   }

   void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
   {
      shader->Bind();
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

      vertexArray->Bind();
      RenderCommand::DrawIndexed(vertexArray);
   }
}
