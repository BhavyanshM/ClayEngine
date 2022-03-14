//
// Created by quantum on 11/5/21.
//

#ifndef CLAYENGINE_MESHTOOLS_H
#define CLAYENGINE_MESHTOOLS_H

#include "Scene/Mesh/Model.h"
#include "Scene/Mesh/TriangleMesh.h"
#include "Scene/Mesh/LineMesh.h"
#include "Manifolds/SurfaceParameters.h"

namespace Clay
{
   class MeshTools
   {
      public:
         static void Circle(Ref<TriangleMesh>& model, uint16_t vertices);
         static void Cylinder(Ref<TriangleMesh>& model, uint16_t vertices, float radius = 0.25f, float height = 1.0f);
         static void Cuboid(Ref<TriangleMesh>& model, float height, float width, float length);
         static void Sphere(Ref<TriangleMesh>& model, float radius, int sectors, int stacks, const SurfaceParameters& params = SurfaceParameters(), float dt = 0);
         static void Surface(Ref<TriangleMesh>& model, int uSteps, int vSteps);
         static void Torus(Ref<TriangleMesh>& model, float innerRadius, float outerRadius, int innerCount, int outerCount);
         static void LoadOFF(Ref<TriangleMesh>& model, const std::string& filename);
         static void LoadOBJ(Ref<TriangleMesh>& model, const std::string& filename);
         static void CoordinateAxes(Ref<TriangleMesh>& model);
         static void BoundingBox(Ref<LineMesh>& model, float height, float width, float length);
   };


}

#endif //CLAYENGINE_MESHTOOLS_H
