//
// Created by quantum on 6/17/21.
//


#include "Renderer.h"

namespace Clay
{

   Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

   void Renderer::Init()
   {
      RenderCommand::Init();
//      Renderer2D::Init();

      s_PointData.PointVertexArray = VertexArray::Create();
      s_PointData.PointVertexBuffer = VertexBuffer::Create(s_PointData.MaxPointVertices * sizeof(PointVertex));

      BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"}
      };
      s_PointData.PointVertexBuffer->SetLayout(layout);
      s_PointData.PointVertexArray->AddVertexBuffer(s_PointData.PointVertexBuffer);
      s_PointData.PointVertexBufferBase = new PointVertex[s_PointData.MaxPointVertices];

      uint32_t* pointIndices = new uint32_t[s_PointData.MaxPointIndices];
      for(uint32_t i = 0; i< s_PointData.MaxPointIndices; i++)
      {
         pointIndices[i] = i;
      }
      Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(pointIndices, s_PointData.MaxPointIndices);
      s_PointData.PointVertexArray->SetIndexBuffer(indexBuffer);
      delete[] pointIndices;

      s_PointData.MeshShader = Shader::Create(std::string(ASSETS_PATH) + std::string("Shaders/PointCloudShader.glsl"));
      s_PointData.MeshShader->Bind();
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
      s_PointData.MeshShader->Bind();
      s_PointData.MeshShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
      s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

      s_PointData.PointIndexCount = 0;
      s_PointData.PointVertexBufferPtr = s_PointData.PointVertexBufferBase;
   }

   void Renderer::EndScene()
   {
      uint32_t dataSize = (uint8_t*)s_PointData.PointVertexBufferPtr - (uint8_t*) s_PointData.PointVertexBufferBase;
      s_PointData.PointVertexBuffer->SetData(s_PointData.PointVertexBufferBase, dataSize);

      Flush();
   }

   void Renderer::Flush()
   {
      RenderCommand::DrawIndexed(s_PointData.PointVertexArray, s_PointData.PointIndexCount, RendererAPI::MODE::Points);
      s_PointData.Stats.DrawCalls++;
   }

   void Renderer::FlushAndReset()
   {
      EndScene();
      CLAY_LOG_INFO("FlushAndReset(): {}", s_PointData.PointIndexCount);
      s_PointData.PointIndexCount = 0;
      s_PointData.PointVertexBufferPtr = s_PointData.PointVertexBufferBase;
   }

   void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform, uint32_t mode)
   {
      shader->Bind();
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
      std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat4("u_Color", glm::vec4(0.3,0.8,0.3,1));

      vertexArray->Bind();
      RenderCommand::DrawIndexed(vertexArray, 0, mode);
      s_PointData.Stats.VertexCount += vertexArray->GetIndexBuffer()->GetCount();
      s_PointData.Stats.DrawCalls++;
   }

   void Renderer::Submit(const Ref<Model>& model)
   {
      Ref<Shader> shader = model->GetShader();
      shader->Bind();
      shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      shader->SetMat4("u_Transform", model->GetTransformToWorld());
      shader->SetFloat4("u_Color", model->GetColor());

      Ref<VertexArray> vertexArray = model->GetVertexArray();
      vertexArray->Bind();
      RenderCommand::DrawIndexed(vertexArray, 0, model->GetType());
      vertexArray->Unbind();
      shader->Unbind();
      s_PointData.Stats.VertexCount += vertexArray->GetIndexBuffer()->GetCount();
      s_PointData.Stats.DrawCalls++;
   }

   void Renderer::SubmitPoints(const Ref<Model>& model)
   {
      CLAY_PROFILE_FUNCTION();

      s_PointData.MeshShader->Bind();
      s_PointData.MeshShader->SetMat4("u_Transform", model->GetTransformToWorld());

      CLAY_LOG_INFO("Points: {}", model->GetSize());

      if(s_PointData.PointIndexCount + model->GetSize() >= s_PointData.MaxPointIndices)
         FlushAndReset();

      for(uint32_t i = 0; i<model->GetSize(); i++)
      {
         s_PointData.PointVertexBufferPtr->Position = {model->GetMesh()->_vertices[i*3 + 0],
                                                       model->GetMesh()->_vertices[i*3 + 1],
                                                       model->GetMesh()->_vertices[i*3 + 2]};
         s_PointData.PointVertexBufferPtr->Color = model->GetColor();
         s_PointData.PointVertexBufferPtr++;
      }
      s_PointData.PointIndexCount += model->GetSize();
      s_PointData.Stats.VertexCount += model->GetSize();
   }

   Renderer::Statistics Renderer::GetStats()
   {
      return s_PointData.Stats;
   }

   void Renderer::ResetStats()
   {
      s_PointData.Stats.TriangleCount = 0;
      s_PointData.Stats.DrawCalls = 0;
      s_PointData.Stats.VertexCount = 0;
   }
}
