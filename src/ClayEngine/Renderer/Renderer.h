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
         inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();}

         static void BeginScene(OrthographicCamera& camera);
         static void EndScene();
         static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

      private:
         struct SceneData
         {
            glm::mat4 ViewProjectionMatrix;
         };

         static SceneData* s_SceneData;

   };
}

#endif //CLAYENGINE_RENDERER_H
