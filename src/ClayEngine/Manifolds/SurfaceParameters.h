//
// Created by quantum on 11/26/21.
//

#ifndef CLAYENGINE_SURFACEPARAMETERS_H
#define CLAYENGINE_SURFACEPARAMETERS_H

#include "eigen3/Eigen/Core"

namespace Clay
{
   class SurfaceParameters
   {
      public:

         SurfaceParameters();

         const Eigen::VectorXf& GetParams() const {return _params;}
         const Eigen::VectorXf& GetGradient() const {return _grad;}
         float CalculateHeight(float u, float v) const;

      private:
         Eigen::VectorXf _params;
         Eigen::VectorXf _grad;
   };
}



#endif //CLAYENGINE_SURFACEPARAMETERS_H
