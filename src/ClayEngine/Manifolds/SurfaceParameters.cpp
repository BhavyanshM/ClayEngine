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
      _params = Eigen::VectorXf(6);
      _params << 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f;
   }

   float SurfaceParameters::CalculateHeight(float u, float v, float dt) const
   {
      return 5 * cosf(u/2) + 5 * sin(v/3 + dt);
   }
}