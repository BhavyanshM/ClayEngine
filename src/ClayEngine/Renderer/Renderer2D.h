//
// Created by quantum on 6/29/21.
//

#ifndef CLAYENGINE_RENDERER2D_H
#define CLAYENGINE_RENDERER2D_H

#include "Camera.h"
#include "Texture.h"

namespace Clay
{



   class Renderer2D
   {


      public:
         static void Init();
         static void Shutdown();
         static void OnWindowResize(uint32_t width, uint32_t height);

         static void BeginScene(const Camera& camera);
         static void EndScene();

         static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
         static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

         static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
         static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);

         static void Flush();


         struct Statistics
         {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() {return QuadCount * 4;}
            uint32_t GetTotalIndexCount() {return QuadCount * 6;}
         };


         static Statistics GetStats();
         static void ResetStats();

      private:
         static void FlushAndReset();

   };

}

#endif //CLAYENGINE_RENDERER2D_H
