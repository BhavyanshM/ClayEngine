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

         static void Shutdown();
         static void OnWindowResize(uint32_t width, uint32_t height);

         static void BeginScene(Camera& camera);
         static void Flush();
         static void FlushAndReset();
         static void EndScene();
         static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), uint32_t mode = RendererAPI::MODE::Triangles);
         //         static void Submit(const Ref<PointCloud>& cloud);
         static void Submit(const Ref<Model>& model);
         static void SubmitPoints(const Ref<Model>& model);

         inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();}

         struct Statistics
         {
            uint32_t DrawCalls = 0;
            uint32_t TriangleCount = 0;
            uint32_t VertexCount = 0;

            uint32_t GetTotalVertexCount() {return (VertexCount != 0) ? VertexCount : TriangleCount * 3;}
            uint32_t GetTotalIndexCount() {return TriangleCount * 3;}
         };

         static Statistics GetStats();
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
   };

   struct LineVertex
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
      static const uint32_t MaxEntities = 200000;

      static const uint32_t MaxPointVertices = MaxEntities;
      static const uint32_t MaxPointIndices = MaxEntities;

      static const uint32_t MaxLineVertices = MaxEntities * 2;
      static const uint32_t MaxLineIndices = MaxEntities * 2;

      static const uint32_t MaxTriangleVertices = MaxEntities * 3;
      static const uint32_t MaxTriangleIndices = MaxEntities * 3;

      static const uint32_t MaxTextureSlots = 32; // TODO: Renderer Capabilities

      Ref<VertexArray> PointVertexArray;
      Ref<VertexBuffer> PointVertexBuffer;

      Ref<VertexArray> LineVertexArray;
      Ref<VertexBuffer> LineVertexBuffer;

      Ref<VertexArray> TriangleVertexArray;
      Ref<VertexBuffer> TriangleVertexBuffer;

      Ref<Shader> MeshShader;
      Ref<Shader> TextureShader;
      Ref<Texture2D> WhiteTexture;

      uint32_t TriangleIndexCount = 0;
      T* TriangleVertexBufferBase = nullptr;
      T* TriangleVertexBufferPtr = nullptr;

      uint32_t LineIndexCount = 0;
      T* LineVertexBufferBase = nullptr;
      T* LineVertexBufferPtr = nullptr;

      uint32_t PointIndexCount = 0;
      T* PointVertexBufferBase = nullptr;
      T* PointVertexBufferPtr = nullptr;

      std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
      uint32_t TextureSlotIndex = 1; // 0: WhiteTexture

      Renderer::Statistics Stats;
   };
   static RendererData<PointVertex> s_PointData;
   static RendererData<LineVertex> s_LineData;
   static RendererData<TriangleVertex> s_TriangleData;
}

#endif //CLAYENGINE_RENDERER_H
