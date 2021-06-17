//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_BUFFER_H
#define CLAYENGINE_BUFFER_H

#include "ClayHeaders.h"
#include "Renderer.h"
#include "Log.h"

namespace Clay
{
   class VertexBuffer
   {
      public:
         virtual ~VertexBuffer() {};

         virtual void Bind() const = 0;
         virtual void Unbind() const = 0;

         virtual uint32_t GetCount() const = 0;

         static VertexBuffer* Create(float* vertices, uint32_t count);
   };

   class IndexBuffer
   {
      public:
         virtual ~IndexBuffer() {};

         virtual void Bind() const = 0;
         virtual void Unbind() const = 0;

         virtual uint32_t GetCount() const = 0;

         static IndexBuffer* Create(uint32_t * indices, uint32_t count);

   };
}

#endif //CLAYENGINE_BUFFER_H
