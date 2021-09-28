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

         static void EndScene();
         static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), uint32_t mode = RendererAPI::MODE::Triangles);
//         static void Submit(const Ref<PointCloud>& cloud);
         static void Submit(const Ref<Model>& model);

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
}

#endif //CLAYENGINE_RENDERER_H
