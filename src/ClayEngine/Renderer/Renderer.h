//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_RENDERER_H
#define CLAYENGINE_RENDERER_H

#include "Core/ClayHeaders.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Platforms/OpenGL/OpenGLShader.h"
#include "Core/Core.h"
#include "Scene/Mesh/PointCloud.h"
#include "Renderer2D.h"
#include "RenderCommand.h"
#include "VertexArray.h"

class VertexArray;

namespace Clay
{
   class Renderer
   {
      public:

         static void Init();
         static void InitPointData();
         static void InitLineData();
         static void InitTriangleData();
         static void Shutdown();
         static void OnWindowResize(uint32_t width, uint32_t height);

         static void BeginScene(Camera& camera);
         static void Flush();
         static void FlushAndReset();
         static void EndScene();

         static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), uint32_t mode = RendererAPI::MODE::Triangles);
         static void Submit(const Ref<Model>& model);
         static void SubmitPoints(const Ref<Model>& model);
         static void SubmitLines(const Ref<Model>& model);
         static void SubmitTriangles(const Ref<Model>& model);
         static void SubmitPointCloudComponents(const Ref<Model>& model);

         inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();}

         struct Statistics
         {
            uint32_t DrawCalls = 0;
            uint32_t TriangleCount = 0;
            uint32_t VertexCount = 0;

            uint32_t GetTotalVertexCount() {return (VertexCount != 0) ? VertexCount : TriangleCount * 3;}
            uint32_t GetTotalIndexCount() {return TriangleCount * 3;}
         };

         static Statistics GetPointStats();
         static Statistics GetLlineStats();
         static Statistics GetTriangleStats();

         static void ResetStats();

      private:
         struct SceneData
         {
            glm::mat4 ViewProjectionMatrix;
         };

         static SceneData* s_SceneData;

   };

   // Vertex Types and Renderer Data +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

   struct PointVertex
   {
      glm::vec3 Position;
      glm::vec4 Color;
      int Id;
   };

   struct LineVertex
   {
      glm::vec3 Position;
   };

   struct TriangleVertex
   {
      glm::vec3 Position;
      int Id;
   };

   template <typename T> // PointVertex or TriangleVertex
   struct RendererData
   {
      static const uint32_t MaxPoints = 100000;
      static const uint32_t MaxLines = 200000;
      static const uint32_t MaxTriangles = 1000000;
      static const uint32_t MaxTextureSlots = 32; // TODO: Renderer Capabilities

      int CloudId = 0;
      int LastIndex = 0;

      Ref<VertexArray> vertexArray;
      Ref<VertexBuffer> vertexBuffer;
      Ref<IndexBuffer> indexBuffer;
      Ref<Shader> MeshShader;
      Ref<Shader> TextureShader;
      Ref<Texture2D> WhiteTexture;

      uint32_t IndexCount = 0;
      T* vertexBufferBase = nullptr;
      T* vertexBufferPtr = nullptr;

      std::vector<glm::mat4> Transforms;

      std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
      uint32_t TextureSlotIndex = 1; // 0: WhiteTexture

      Renderer::Statistics Stats;
   };
   static RendererData<PointVertex> s_PointData;
   static RendererData<LineVertex> s_LineData;
   static RendererData<TriangleVertex> s_TriangleData;
}

#endif //CLAYENGINE_RENDERER_H
