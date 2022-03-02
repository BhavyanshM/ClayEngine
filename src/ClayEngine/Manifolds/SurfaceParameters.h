//
// Created by quantum on 11/26/21.
//

#ifndef CLAYENGINE_SURFACEPARAMETERS_H
#define CLAYENGINE_SURFACEPARAMETERS_H

namespace Clay
{
   class SurfaceParameters
   {
      public:

         SurfaceParameters();

         float CalculateHeight(float u, float v, float dt) const;

   };
}



#endif //CLAYENGINE_SURFACEPARAMETERS_H
