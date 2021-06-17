//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_RENDERER_H
#define CLAYENGINE_RENDERER_H

#include "ClayHeaders.h"

namespace Clay
{
   enum class RendererAPI
   {
         None = 0, OpenGL = 1
   };

   class Renderer
   {
      public:
         inline static RendererAPI GetAPI() { return s_RendererAPI;}

      private:

         static RendererAPI s_RendererAPI;
   };
}

#endif //CLAYENGINE_RENDERER_H
