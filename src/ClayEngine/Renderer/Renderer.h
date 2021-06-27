//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_RENDERER_H
#define CLAYENGINE_RENDERER_H

#include "Core/ClayHeaders.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Platforms/OpenGL/OpenGLShader.h"
#include "Core/Core.h"

class VertexArray;

namespace Clay
{
   class Renderer
   {
      public:

         static void Init();
         static void OnWindowResize(uint32_t width, uint32_t height);

         static void BeginScene(OrthographicCamera& camera);

         static void EndScene();
         static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

         inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();}

      private:
         struct SceneData
         {
            glm::mat4 ViewProjectionMatrix;
         };

         static SceneData* s_SceneData;

   };
}

#endif //CLAYENGINE_RENDERER_H
