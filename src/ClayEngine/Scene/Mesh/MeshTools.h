//
// Created by quantum on 11/5/21.
//

#ifndef CLAYENGINE_MESHTOOLS_H
#define CLAYENGINE_MESHTOOLS_H

#include "Scene/Mesh/Model.h"
#include "Scene/Mesh/TriangleMesh.h"

namespace Clay
{
   class MeshTools
   {
      public:
         static void Circle(Ref<TriangleMesh>& model, uint16_t vertices);
         static void Cylinder(Ref<TriangleMesh>& model, uint16_t vertices, float height = 1.0f);


      private:

   };


}

#endif //CLAYENGINE_MESHTOOLS_H
