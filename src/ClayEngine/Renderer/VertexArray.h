//
// Created by quantum on 6/18/21.
//

#ifndef CLAYENGINE_VERTEXARRAY_H
#define CLAYENGINE_VERTEXARRAY_H

#include "ClayHeaders.h"
#include "Buffer.h"
#include "Core.h"

namespace Clay
{
   class VertexArray
   {
      public:
         virtual ~VertexArray() {};

         virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
         virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

         // TODO-Clay: Add getter for vertex buffers(s): GetVertexBuffers()
         virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

         virtual void Bind() = 0;
         virtual void Unbind() = 0;

         static VertexArray* Create();
   };
}


#endif //CLAYENGINE_VERTEXARRAY_H
