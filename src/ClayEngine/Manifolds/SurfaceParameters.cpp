//
// Created by quantum on 11/26/21.
//

#include "Core/Log.h"
#include "SurfaceParameters.h"
#include "iostream"

namespace Clay
{
   SurfaceParameters::SurfaceParameters()
   {
   }

   float SurfaceParameters::CalculateHeight(float u, float v, float dt) const
   {
      return 5 * cosf(u/2) + 5 * sin(v/3 + dt);
   }
}