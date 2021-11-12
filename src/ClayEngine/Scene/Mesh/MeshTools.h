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
         static void Cuboid(Ref<TriangleMesh>& model, float height, float width, float length);
         static void Sphere(Ref<TriangleMesh>& model, float radius, int sectors, int stacks);
         static void Surface(Ref<TriangleMesh>& model, int uSteps, int vSteps);

      private:

   };


}

#endif //CLAYENGINE_MESHTOOLS_H
