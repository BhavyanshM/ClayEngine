//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_RENDERER_H
#define CLAYENGINE_RENDERER_H

#include "ClayHeaders.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

class VertexArray;

namespace Clay
{
   class Renderer
   {
      public:
         inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();}

         static void BeginScene(OrthographicCamera& camera);
         static void EndScene();
         static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

      private:
         struct SceneData
         {
            glm::mat4 ViewProjectionMatrix;
         };

         static SceneData* s_SceneData;

   };
}

#endif //CLAYENGINE_RENDERER_H
