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
         PointCloud() = default;
         PointCloud(const std::string& filename, const glm::vec4& color);

         void Upload() override;
         void Reset() override;
         void Insert(float x, float y, float z);

         uint32_t GetSize() const { return _index;}


      private:
         static const uint32_t MAX_POINTS = 400000;
         uint32_t _index = 0;
         uint32_t _indices[MAX_POINTS];

         float _vertices[MAX_POINTS * 3];
   };
}

#endif //CLAYENGINE_POINTCLOUD_H
