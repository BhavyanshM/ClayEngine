//
// Created by quantum on 9/24/21.
//

#ifndef CLAYENGINE_POINTCLOUD_H
#define CLAYENGINE_POINTCLOUD_H

#include "Core/ClayHeaders.h"
#include "Core/Core.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"

namespace Clay
{
   class PointCloud
   {
      public:
         PointCloud() = default;
         PointCloud(const std::string& filename);

         Ref<VertexBuffer> GetVertexBuffer() const { return _vertexBuffer;}
         Ref<VertexArray> GetVertexArray() const { return _vertexArray;}

      private:
         Ref<VertexArray> _vertexArray;
         Ref<IndexBuffer> _indexBuffer;
         Ref<VertexBuffer> _vertexBuffer;
   };
}

#endif //CLAYENGINE_POINTCLOUD_H
