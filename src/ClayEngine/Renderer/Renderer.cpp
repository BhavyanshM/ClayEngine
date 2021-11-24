//
// Created by quantum on 6/17/21.
//


/*
 * RESOUCES +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * StackOverFlow Responses to FAQ on VAO, VBO and binding.
 * https://gamedev.stackexchange.com/questions/99236/what-state-is-stored-in-an-opengl-vertex-array-object-vao-and-how-do-i-use-the
 * https://stackoverflow.com/questions/42411310/do-i-have-to-call-glvertexattribpointer-each-frame-for-each-rendered-mesh
 * https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
 * https://stackoverflow.com/questions/26552642/when-is-what-bound-to-a-vao
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * */

#include "Renderer.h"

namespace Clay
{

   Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

   void Renderer::Init()
   {
      RenderCommand::Init();
//      Renderer2D::Init();

      if(EN_LINES) Renderer::InitLineData();
      if(EN_POINTS) Renderer::InitPointData();
      if(EN_TRIANGLES) Renderer::InitTriangleData();

   }

   void Renderer::InitPointData()
   {
      s_PointData.vertexArray = VertexArray::Create();
      s_PointData.vertexBuffer = VertexBuffer::Create(s_PointData.MaxPoints * sizeof(PointVertex));

      BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Float, "a_Id"}
      };
      s_PointData.vertexBuffer->SetLayout(layout);
      s_PointData.vertexArray->AddVertexBuffer(s_PointData.vertexBuffer);
      s_PointData.vertexBufferBase = new PointVertex[s_PointData.MaxPoints];

      uint32_t* pointIndices = new uint32_t[s_PointData.MaxPoints];
      for(uint32_t i = 0; i< s_PointData.MaxPoints; i++)
      {
         pointIndices[i] = i;
      }
      Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(pointIndices, s_PointData.MaxPoints);
      s_PointData.vertexArray->SetIndexBuffer(indexBuffer);
      delete[] pointIndices;

      s_PointData.MeshShader = Shader::Create(std::string(ASSETS_PATH) + std::string("Shaders/PointCloudShader.glsl"));
      s_PointData.MeshShader->Bind();
   }

   void Renderer::InitTriangleData()
   {
      s_TriangleData.vertexArray = VertexArray::Create();
      s_TriangleData.vertexBuffer = VertexBuffer::Create(s_TriangleData.MaxTriangles * 3 * sizeof(TriangleVertex));

      BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Float, "a_Id"}
      };
      s_TriangleData.vertexBuffer->SetLayout(layout);
      s_TriangleData.vertexArray->AddVertexBuffer(s_TriangleData.vertexBuffer);
      s_TriangleData.vertexBufferBase = new TriangleVertex[s_TriangleData.MaxTriangles * 3];


      s_TriangleData.indexBuffer = IndexBuffer::Create();
      uint32_t offset = 0;

      s_TriangleData.vertexArray->SetIndexBuffer(s_TriangleData.indexBuffer);
      s_TriangleData.MeshShader = Shader::Create(std::string(ASSETS_PATH) + std::string("Shaders/TriangleShader.glsl"));
      s_TriangleData.MeshShader->Bind();
   }

   void Renderer::InitLineData()
   {
      s_LineData.vertexArray = VertexArray::Create();
      s_LineData.vertexBuffer = VertexBuffer::Create(s_LineData.MaxLines * 2 * sizeof(LineVertex));

      BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"}
      };
      s_LineData.vertexBuffer->SetLayout(layout);
      s_LineData.vertexArray->AddVertexBuffer(s_LineData.vertexBuffer);
      s_LineData.vertexBufferBase = new LineVertex[s_LineData.MaxLines * 2];

      uint32_t* lineIndices = new uint32_t[s_LineData.MaxLines * 2];
      uint32_t offset = 0;
      for(uint32_t i = 0; i< s_LineData.MaxLines * 2; i+=2)
      {
         lineIndices[i+0] = offset + 0;
         lineIndices[i+1] = offset + 1;
         offset += 2;
      }
      Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(lineIndices, s_LineData.MaxLines * 2);
      s_LineData.vertexArray->SetIndexBuffer(indexBuffer);
      delete[] lineIndices;

      s_LineData.MeshShader = Shader::Create(std::string(ASSETS_PATH) + std::string("Shaders/LineShader.glsl"));
      s_LineData.MeshShader->Bind();
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

      if(EN_TRIANGLES){
         s_TriangleData.IndexCount = 0;
         s_TriangleData.LastIndex = 0;
         s_TriangleData.vertexBufferPtr = s_TriangleData.vertexBufferBase;
      }
      if(EN_POINTS){
         s_PointData.IndexCount = 0;
         s_PointData.vertexBufferPtr = s_PointData.vertexBufferBase;
      }

      if(EN_LINES){
         s_LineData.IndexCount = 0;
         s_LineData.vertexBufferPtr = s_LineData.vertexBufferBase;
      }

   }

   void Renderer::FlushAndReset()
   {
      EndScene();

      if(EN_TRIANGLES){
         s_TriangleData.IndexCount = 0;
         s_TriangleData.LastIndex = 0;
         s_TriangleData.vertexBufferPtr = s_TriangleData.vertexBufferBase;
      }

      if(EN_POINTS){
         s_PointData.IndexCount = 0;
         s_PointData.vertexBufferPtr = s_PointData.vertexBufferBase;
      }

      if(EN_LINES){
         s_LineData.IndexCount = 0;
         s_LineData.vertexBufferPtr = s_LineData.vertexBufferBase;
      }

   }

   void Renderer::EndScene()
   {
      uint32_t dataSize = 0;

      if(EN_TRIANGLES){
         dataSize = (uint8_t *) s_TriangleData.vertexBufferPtr - (uint8_t *) s_TriangleData.vertexBufferBase;
         s_TriangleData.vertexBuffer->SetData(s_TriangleData.vertexBufferBase, dataSize);
         CLAY_LOG_INFO("Setting Triangle Data: {}", (int)(s_TriangleData.vertexBufferPtr - s_TriangleData.vertexBufferBase));
      }

      if(EN_POINTS){
         dataSize = (uint8_t *) s_PointData.vertexBufferPtr - (uint8_t *) s_PointData.vertexBufferBase;
         s_PointData.vertexBuffer->SetData(s_PointData.vertexBufferBase, dataSize);
      }

      if(EN_LINES){
         dataSize = (uint8_t *) s_LineData.vertexBufferPtr - (uint8_t *) s_LineData.vertexBufferBase;
         s_LineData.vertexBuffer->SetData(s_LineData.vertexBufferBase, dataSize);
      }

      Flush();
   }

   void Renderer::Flush()
   {
      if(EN_TRIANGLES){
         s_TriangleData.MeshShader->Bind();
         s_TriangleData.vertexArray->Bind();
         s_TriangleData.indexBuffer->Upload();
         RenderCommand::DrawIndexed(s_TriangleData.vertexArray, s_TriangleData.indexBuffer->GetCount(), RendererAPI::MODE::Triangles);
         s_TriangleData.vertexArray->Unbind();
         s_TriangleData.MeshShader->Unbind();
         s_TriangleData.Stats.DrawCalls++;
         s_TriangleData.Transforms.clear();
         s_TriangleData.CloudId = 0;
      }

      if(EN_POINTS){
         s_PointData.MeshShader->Bind();
         s_PointData.vertexArray->Bind();
         RenderCommand::DrawIndexed(s_PointData.vertexArray, s_PointData.IndexCount, RendererAPI::MODE::Points);
         s_PointData.vertexArray->Unbind();
         s_PointData.MeshShader->Unbind();
         s_PointData.Stats.DrawCalls++;
         s_PointData.Transforms.clear();
         s_PointData.CloudId = 0;
      }



      if(EN_LINES){
         //      RenderCommand::DrawIndexed(s_LineData.vertexArray, s_LineData.IndexCount, RendererAPI::MODE::Lines);
         s_LineData.Stats.DrawCalls++;
         s_LineData.Transforms.clear();
         s_LineData.CloudId = 0;
      }
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
      if(model->GetType() == RendererAPI::MODE::Triangles && EN_TRIANGLES)
      {
         SubmitTriangles(model);
      }
      if(model->GetType() == RendererAPI::MODE::Lines && EN_LINES)
      {
         SubmitLines(model);
      }
      if(model->GetType() == RendererAPI::MODE::Points && EN_POINTS)
      {
         SubmitPoints(model);
      }
   }

   void Renderer::SubmitPoints(const Ref<Model>& model)
   {
      CLAY_PROFILE_FUNCTION();
      s_PointData.MeshShader->Bind();
      if(s_PointData.IndexCount + model->GetSize() >= s_PointData.MaxPoints)
         FlushAndReset();

      s_PointData.MeshShader->Bind();
      s_PointData.MeshShader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      s_PointData.Transforms.emplace_back(model->GetTransformToWorld());
      s_PointData.MeshShader->SetMat4Array("u_Transforms", s_PointData.Transforms, 32);
      for(uint32_t i = 0; i<model->GetSize(); i++)
      {
         s_PointData.vertexBufferPtr->Position = {model->GetMesh()->_vertices[i*3 + 0],
                                                       model->GetMesh()->_vertices[i*3 + 1],
                                                       model->GetMesh()->_vertices[i*3 + 2]};
         s_PointData.vertexBufferPtr->Color = model->GetColor();
         s_PointData.vertexBufferPtr->Id = s_PointData.CloudId;
         s_PointData.vertexBufferPtr++;
      }
      s_PointData.IndexCount += model->GetSize();
      s_PointData.Stats.VertexCount += model->GetSize();
      s_PointData.CloudId++;
   }

   void Renderer::SubmitPointCloudComponents(const Ref<Model>& model)
   {
      CLAY_PROFILE_FUNCTION();
      s_PointData.MeshShader->Bind();
      if(s_PointData.IndexCount + model->GetSize() >= s_PointData.MaxPoints)
         FlushAndReset();

      s_PointData.MeshShader->Bind();
      s_PointData.MeshShader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      s_PointData.Transforms.emplace_back(model->GetTransformToWorld());
      s_PointData.MeshShader->SetMat4Array("u_Transforms", s_PointData.Transforms, 32);
      for(uint32_t i = 0; i<model->GetSize(); i++)
      {
         s_PointData.vertexBufferPtr->Position = {model->GetMesh()->_vertices[i*3 + 0],
                                                       model->GetMesh()->_vertices[i*3 + 1],
                                                       model->GetMesh()->_vertices[i*3 + 2]};
         s_PointData.vertexBufferPtr->Color = {(float)(model->GetMesh()->_partIds[i] * 123 % 255) / 255.0f,
                                                    (float)(model->GetMesh()->_partIds[i] * 321 % 255) / 255.0f,
                                                    (float)(model->GetMesh()->_partIds[i] * 432 % 255) / 255.0f,
                                                    1.0f};
//         s_PointData.vertexBufferPtr->Color = {1.0f, 0.0f, 1.0f,1.0f};
         s_PointData.vertexBufferPtr->Id = s_PointData.CloudId;
         s_PointData.vertexBufferPtr++;
      }
      s_PointData.IndexCount += model->GetSize();
      s_PointData.Stats.VertexCount += model->GetSize();
      s_PointData.CloudId++;
   }

   void Renderer::SubmitLines(const Ref<Model>& model)
   {
      CLAY_PROFILE_FUNCTION();
      s_LineData.MeshShader->Bind();
      if(s_LineData.IndexCount + model->GetSize() >= s_LineData.MaxLines * 2)
         FlushAndReset();

      s_LineData.MeshShader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      s_LineData.MeshShader->SetMat4("u_Transform", model->GetTransformToWorld());
      s_LineData.MeshShader->SetFloat4("u_Color", model->GetColor());

      s_LineData.MeshShader->Bind();
      for(uint32_t i = 0; i<model->GetSize(); i++)
      {
         s_LineData.vertexBufferPtr->Position = {model->GetMesh()->_vertices[i*3 + 0],
                                                       model->GetMesh()->_vertices[i*3 + 1],
                                                       model->GetMesh()->_vertices[i*3 + 2]};
         s_LineData.vertexBufferPtr++;
      }
      s_LineData.IndexCount += model->GetSize();
      s_LineData.Stats.VertexCount += model->GetSize();
   }

   void Renderer::SubmitTriangles(const Ref<Model>& model)
   {
      CLAY_PROFILE_FUNCTION();
      s_TriangleData.MeshShader->Bind();
      if(s_TriangleData.IndexCount + model->GetSize() >= s_TriangleData.MaxTriangles * 3)
         FlushAndReset();


      s_TriangleData.Transforms.emplace_back(model->GetTransformToWorld());
      s_TriangleData.MeshShader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
      s_TriangleData.MeshShader->SetMat4Array("u_Transforms", s_TriangleData.Transforms, 32);
      s_TriangleData.MeshShader->SetFloat4("u_ObjectColor", model->GetColor());
      s_TriangleData.MeshShader->SetFloat4("u_LightColor", {0.4, 0.9, 0.9, 1.0});
      s_TriangleData.MeshShader->SetFloat("u_AmbientStrength", 0.5);

      for(uint32_t i = 0; i<model->GetSize(); i++)
      {
         s_TriangleData.vertexBufferPtr->Position = {model->GetMesh()->_vertices[i*3 + 0],
                                                     model->GetMesh()->_vertices[i*3 + 1],
                                                     model->GetMesh()->_vertices[i*3 + 2]};
         s_TriangleData.vertexBufferPtr->Color = model->GetColor();
         s_TriangleData.vertexBufferPtr->Id = (float)s_TriangleData.CloudId;
         s_TriangleData.vertexBufferPtr++;
      }

      for(uint32_t i = 0; i< model->GetMesh()->_indices.size(); i++)
      {
         s_TriangleData.indexBuffer->AddIndex(model->GetMesh()->_indices[i] + s_TriangleData.LastIndex);
      }


      s_TriangleData.LastIndex += model->GetMesh()->_vertices.size() / 3;
      s_TriangleData.IndexCount += model->GetMesh()->_indices.size() / 3;
      s_TriangleData.Stats.TriangleCount = s_TriangleData.IndexCount;
      s_TriangleData.Stats.VertexCount += model->GetSize();
      s_TriangleData.CloudId++;

      CLAY_LOG_INFO("TriangleMesh: {} {} {} {}", s_TriangleData.LastIndex, s_TriangleData.indexBuffer->GetIndices().size(), s_TriangleData.CloudId, s_TriangleData.Transforms.size());

   }

   void Renderer::ResetStats()
   {
      s_PointData.Stats.TriangleCount = 0;
      s_PointData.Stats.DrawCalls = 0;
      s_PointData.Stats.VertexCount = 0;

      s_LineData.Stats.TriangleCount = 0;
      s_LineData.Stats.DrawCalls = 0;
      s_LineData.Stats.VertexCount = 0;

      s_TriangleData.Stats.TriangleCount = 0;
      s_TriangleData.Stats.DrawCalls = 0;
      s_TriangleData.Stats.VertexCount = 0;

   }

   Renderer::Statistics Renderer::GetPointStats() { return s_PointData.Stats; }
   Renderer::Statistics Renderer::GetLlineStats() { return s_LineData.Stats; }
   Renderer::Statistics Renderer::GetTriangleStats() { return s_TriangleData.Stats; }
}
