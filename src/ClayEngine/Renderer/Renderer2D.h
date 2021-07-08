//
// Created by quantum on 6/29/21.
//

#ifndef CLAYENGINE_RENDERER2D_H
#define CLAYENGINE_RENDERER2D_H

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Clay
{

   class Renderer2D
   {
      public:
         static void Init();
         static void Shutdown();
         static void OnWindowResize(uint32_t width, uint32_t height);

         static void BeginScene(const OrthographicCamera& camera);
         static void EndScene();

         static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
         static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

         static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
         static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);

         static void Flush();

      private:

   };

}

#endif //CLAYENGINE_RENDERER2D_H
