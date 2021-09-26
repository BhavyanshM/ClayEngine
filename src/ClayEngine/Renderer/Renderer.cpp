//
// Created by quantum on 6/17/21.
//


#include "Renderer.h"
#include "Renderer2D.h"
#include "RenderCommand.h"
#include "VertexArray.h"



namespace Clay
{

   struct PointVertex
   {
      glm::vec3 Position;
      glm::vec4 Color;
   };

   struct TriangleVertex
   {
      glm::vec3 Position;
      glm::vec4 Color;
      glm::vec2 TexCoord;
      float TexIndex;
   };

   template <typename T> // PointVertex or TriangleVertex
   struct RendererData
   {
      static const uint32_t MaxTriangles = 20000;
      static const uint32_t MaxVertices = MaxTriangles * 3;
      static const uint32_t MaxIndices = MaxTriangles * 3;
      static const uint32_t MaxTextureSlots = 32; // TODO: Renderer Capabilities

      Ref<VertexArray> TriangleVertexArray;
      Ref<VertexBuffer> TriangleVertexBuffer;
      Ref<Shader> TextureShader;
      Ref<Texture2D> WhiteTexture;

      uint32_t QuadIndexCount = 0;
      T* VertexBufferBase = nullptr;
      T* VertexBufferPtr = nullptr;

      std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
      uint32_t TextureSlotIndex = 1; // 0: WhiteTexture

      Renderer::Statistics Stats;
   };

   static RendererData<PointVertex> s_Data;

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

   void Renderer::BeginScene(Camera& camera)
   {
      s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
   }

   void Renderer::EndScene()
   {
   }

   void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform, uint32_t mode)
   {
      shader->Bind();
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat4("u_Color", glm::vec4(0.3,0.8,0.3,1));

      vertexArray->Bind();
      RenderCommand::DrawIndexed(vertexArray, 0, mode);
      s_Data.Stats.VertexCount += vertexArray->GetIndexBuffer()->GetCount();
      s_Data.Stats.DrawCalls++;
   }

   void Renderer::Submit(const Ref<PointCloud>& cloud)
   {
      Ref<Shader> shader = cloud->GetShader();
      shader->Bind();
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", cloud->GetTransform());
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat4("u_Color", cloud->GetColor());

      Ref<VertexArray> vertexArray = cloud->GetVertexArray();
      vertexArray->Bind();
      RenderCommand::DrawIndexed(vertexArray, 0, RendererAPI::MODE::Points);
      s_Data.Stats.VertexCount += vertexArray->GetIndexBuffer()->GetCount();
      s_Data.Stats.DrawCalls++;
   }

   Renderer::Statistics Renderer::GetStats()
   {
      return s_Data.Stats;
   }

   void Renderer::ResetStats()
   {
      s_Data.Stats.TriangleCount = 0;
      s_Data.Stats.DrawCalls = 0;
      s_Data.Stats.VertexCount = 0;
   }
}
