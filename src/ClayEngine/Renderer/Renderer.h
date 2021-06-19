//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_RENDERER_H
#define CLAYENGINE_RENDERER_H

#include "ClayHeaders.h"
#include "RenderCommand.h"

class VertexArray;

namespace Clay
{
   class Renderer
   {
      public:
         inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI();}

         static void BeginScene();
         static void EndScene();
         static void Submit(const std::shared_ptr<VertexArray>& vertexBuffer);


   };
}

#endif //CLAYENGINE_RENDERER_H
