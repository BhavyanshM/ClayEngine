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

      Renderer::InitPointData();
//      Renderer::InitLineData();

   }

   void Renderer::InitLineData()
   {
      s_LineData.LineVertexArray = VertexArray::Create();
      s_LineData.LineVertexBuffer = VertexBuffer::Create(s_LineData.MaxLineVertices * sizeof(LineVertex));

      BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"}
      };
      s_LineData.LineVertexBuffer->SetLayout(layout);
      s_LineData.LineVertexArray->AddVertexBuffer(s_LineData.LineVertexBuffer);
      s_LineData.LineVertexBufferBase = new LineVertex[s_LineData.MaxLineVertices];

      uint32_t* lineIndices = new uint32_t[s_LineData.MaxLineIndices];
      uint32_t offset = 0;
      for(uint32_t i = 0; i< s_LineData.MaxLineIndices; i+=2)
      {
         lineIndices[i+0] = offset + 0;
         lineIndices[i+1] = offset + 1;
         offset += 2;
      }
      Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(lineIndices, s_LineData.MaxLineIndices);
      s_LineData.LineVertexArray->SetIndexBuffer(indexBuffer);
      delete[] lineIndices;

      s_LineData.MeshShader = Shader::Create(std::string(ASSETS_PATH) + std::string("Shaders/LineShader.glsl"));
      s_LineData.MeshShader->Bind();
   }

   void Renderer::InitPointData()
   {
      s_PointData.PointVertexArray = VertexArray::Create();
      s_PointData.PointVertexBuffer = VertexBuffer::Create(s_PointData.MaxPointVertices * sizeof(PointVertex));

      BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Int, "a_Id"}
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


      s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

      s_PointData.PointIndexCount = 0;
      s_PointData.PointVertexBufferPtr = s_PointData.PointVertexBufferBase;

//      s_LineData.LineIndexCount = 0;
//      s_LineData.LineVertexBufferPtr = s_LineData.LineVertexBufferBase;

//      s_TriangleData.TriangleIndexCount = 0;
//      s_TriangleData.TriangleVertexBufferPtr = s_TriangleData.TriangleVertexBufferBase;
   }

   void Renderer::EndScene()
   {
      uint32_t dataSize = 0;

      dataSize = (uint8_t*)s_PointData.PointVertexBufferPtr - (uint8_t*) s_PointData.PointVertexBufferBase;
      s_PointData.PointVertexBuffer->SetData(s_PointData.PointVertexBufferBase, dataSize);

//      dataSize = (uint8_t*)s_LineData.LineVertexBufferPtr - (uint8_t*) s_LineData.LineVertexBufferBase;
//      s_LineData.LineVertexBuffer->SetData(s_LineData.LineVertexBufferBase, dataSize);

//      dataSize = (uint8_t*)s_TriangleData.TriangleVertexBufferPtr - (uint8_t*) s_TriangleData.TriangleVertexBufferBase;
//      s_TriangleData.TriangleVertexBuffer->SetData(s_TriangleData.TriangleVertexBufferBase, dataSize);

      Flush();
   }

   void Renderer::Flush()
   {
      RenderCommand::DrawIndexed(s_PointData.PointVertexArray, s_PointData.PointIndexCount, RendererAPI::MODE::Points);
//      RenderCommand::DrawIndexed(s_LineData.LineVertexArray, s_LineData.LineIndexCount, RendererAPI::MODE::Lines);
      s_PointData.Stats.DrawCalls++;
      s_PointData.Transforms.clear();
      s_PointData.CloudId = 0;
   }

   void Renderer::FlushAndReset()
   {
      EndScene();
      s_PointData.PointIndexCount = 0;
      s_PointData.PointVertexBufferPtr = s_PointData.PointVertexBufferBase;

//      s_LineData.LineIndexCount = 0;
//      s_LineData.LineVertexBufferPtr = s_LineData.LineVertexBufferBase;
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
      if(s_PointData.PointIndexCount + model->GetSize() >= s_PointData.MaxPointIndices)
         FlushAndReset();

      s_PointData.MeshShader->Bind();
      s_PointData.MeshShader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      s_PointData.Transforms.emplace_back(model->GetTransformToWorld());
      s_PointData.MeshShader->SetMat4Array("u_Transforms", s_PointData.Transforms, 32);
      for(uint32_t i = 0; i<model->GetSize(); i++)
      {
         s_PointData.PointVertexBufferPtr->Position = {model->GetMesh()->_vertices[i*3 + 0],
                                                       model->GetMesh()->_vertices[i*3 + 1],
                                                       model->GetMesh()->_vertices[i*3 + 2]};
         s_PointData.PointVertexBufferPtr->Color = model->GetColor();
         s_PointData.PointVertexBufferPtr->Id = s_PointData.CloudId;
         s_PointData.PointVertexBufferPtr++;
      }
      s_PointData.PointIndexCount += model->GetSize();
      s_PointData.Stats.VertexCount += model->GetSize();
      s_PointData.CloudId++;
   }

   void Renderer::SubmitPointCloudComponents(const Ref<Model>& model)
   {
      CLAY_PROFILE_FUNCTION();
      s_PointData.MeshShader->Bind();
      if(s_PointData.PointIndexCount + model->GetSize() >= s_PointData.MaxPointIndices)
         FlushAndReset();

      s_PointData.MeshShader->Bind();
      s_PointData.MeshShader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      s_PointData.Transforms.emplace_back(model->GetTransformToWorld());
      s_PointData.MeshShader->SetMat4Array("u_Transforms", s_PointData.Transforms, 32);
      for(uint32_t i = 0; i<model->GetSize(); i++)
      {
         s_PointData.PointVertexBufferPtr->Position = {model->GetMesh()->_vertices[i*3 + 0],
                                                       model->GetMesh()->_vertices[i*3 + 1],
                                                       model->GetMesh()->_vertices[i*3 + 2]};
         s_PointData.PointVertexBufferPtr->Color = {(float)(model->GetMesh()->_partIds[i] * 123 % 255) / 255.0f,
                                                    (float)(model->GetMesh()->_partIds[i] * 321 % 255) / 255.0f,
                                                    (float)(model->GetMesh()->_partIds[i] * 432 % 255) / 255.0f,
                                                    1.0f};
//         s_PointData.PointVertexBufferPtr->Color = {1.0f, 0.0f, 1.0f,1.0f};
         s_PointData.PointVertexBufferPtr->Id = s_PointData.CloudId;
         s_PointData.PointVertexBufferPtr++;
      }
      s_PointData.PointIndexCount += model->GetSize();
      s_PointData.Stats.VertexCount += model->GetSize();
      s_PointData.CloudId++;
   }

   void Renderer::SubmitLines(const Ref<Model>& model)
   {
      CLAY_PROFILE_FUNCTION();
      s_LineData.MeshShader->Bind();
      if(s_LineData.LineIndexCount + model->GetSize() >= s_LineData.MaxLineIndices)
         FlushAndReset();

      s_LineData.MeshShader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      s_LineData.MeshShader->SetMat4("u_Transform", model->GetTransformToWorld());
      s_LineData.MeshShader->SetFloat4("u_Color", model->GetColor());

      s_LineData.MeshShader->Bind();
      for(uint32_t i = 0; i<model->GetSize(); i++)
      {
         s_LineData.LineVertexBufferPtr->Position = {model->GetMesh()->_vertices[i*3 + 0],
                                                       model->GetMesh()->_vertices[i*3 + 1],
                                                       model->GetMesh()->_vertices[i*3 + 2]};
         s_LineData.LineVertexBufferPtr++;
      }
      s_LineData.LineIndexCount += model->GetSize();
      s_LineData.Stats.VertexCount += model->GetSize();
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
