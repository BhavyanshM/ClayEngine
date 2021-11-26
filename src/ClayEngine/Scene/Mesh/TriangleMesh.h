//
// Created by quantum on 9/24/21.
//

#ifndef CLAYENGINE_TRIANGLEMESH_H
#define CLAYENGINE_TRIANGLEMESH_H

#include "Scene/Mesh/Model.h"

namespace Clay
{
   class TriangleMesh : public Model
   {
      public:
         TriangleMesh() : Model() {};
         TriangleMesh(const glm::vec4& color, const Ref<Model>& parent);

         void Reset() override;
         void InsertVertex(float x, float y, float z) override;
         void InsertIndex(uint32_t index) override;
         void Print() override;

   };
}

#endif //CLAYENGINE_TRIANGLEMESH_H
