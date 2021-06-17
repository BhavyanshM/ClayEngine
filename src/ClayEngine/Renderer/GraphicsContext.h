//
// Created by quantum on 6/16/21.
//

#ifndef CLAYENGINE_GRAPHICSCONTEXT_H
#define CLAYENGINE_GRAPHICSCONTEXT_H

namespace Clay
{
   class GraphicsContext
   {
      public:
         virtual void Init() = 0;
         virtual void SwapBuffers() = 0;
   };
}

#endif //CLAYENGINE_GRAPHICSCONTEXT_H
