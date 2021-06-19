//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_RENDERER_H
#define CLAYENGINE_RENDERER_H

#include "ClayHeaders.h"

class VertexArray;

namespace Clay
{
   class Renderer
   {
      public:
         inline static RendererAPI GetAPI() { return s_RendererAPI;}

         static void BeginScene();
         static void EndScene();
         static void Submit(const std::shared_ptr<VertexArray>& vertexBuffer);

      private:

         static RendererAPI s_RendererAPI;
   };
}

#endif //CLAYENGINE_RENDERER_H
