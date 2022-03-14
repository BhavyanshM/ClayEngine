//
// Created by quantum on 9/24/21.
//

#ifndef CLAYENGINE_LINEMESH_H
#define CLAYENGINE_LINEMESH_H

#include "Scene/Mesh/Model.h"

namespace Clay
{
   class LineMesh : public Model
   {
      public:
         LineMesh() : Model() {};
         LineMesh(const glm::vec4& color, const Ref<Model>& parent);

         void Reset() override;
         void InsertVertex(float x, float y, float z) override;
         void InsertIndex(uint32_t index) override;
         void Print() override;


   };
}

#endif //CLAYENGINE_LINEMESH_H
