//
// Created by quantum on 6/18/21.
//

#ifndef CLAYENGINE_VERTEXARRAY_H
#define CLAYENGINE_VERTEXARRAY_H

#include "ClayHeaders.h"
#include "Buffer.h"

namespace Clay
{
   class VertexArray
   {
      public:
         virtual ~VertexArray() {};

         virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
         virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
         virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

         virtual void Bind() = 0;
         virtual void Unbind() = 0;

         static VertexArray* Create();
   };
}


#endif //CLAYENGINE_VERTEXARRAY_H
