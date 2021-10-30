//
// Created by quantum on 9/24/21.
//

#ifndef CLAYENGINE_POINTCLOUD_H
#define CLAYENGINE_POINTCLOUD_H

#include "Scene/Mesh/Model.h"

namespace Clay
{
   class PointCloud : public Model
   {
      public:
         PointCloud() : Model() {};
         PointCloud(const glm::vec4& color, const Ref<Model>& parent);

         void Load(const std::string& filename) override;
         void Reset() override;
         void Insert(float x, float y, float z);
         void Print() override;

   };
}

#endif //CLAYENGINE_POINTCLOUD_H
