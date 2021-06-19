//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_OPENGLBUFFER_H
#define CLAYENGINE_OPENGLBUFFER_H

#include "ClayHeaders.h"
#include "Renderer/Buffer.h"

namespace Clay
{
   class OpenGLVertexBuffer : public VertexBuffer
   {
      public:
         OpenGLVertexBuffer(float* vertices, uint32_t count);
         virtual ~OpenGLVertexBuffer();

         virtual void Bind() const override;
         virtual void Unbind() const override;

         virtual const BufferLayout& GetLayout() const override;
         virtual void SetLayout(const BufferLayout& layout) override;

         virtual uint32_t GetCount() const override {return _count;}

      private:
         uint32_t _rendererId;
         uint32_t _count;
         BufferLayout _layout;

   };

   class OpenGLIndexBuffer : public IndexBuffer
   {
      public:
         OpenGLIndexBuffer(uint32_t * indices, uint32_t count);
         virtual ~OpenGLIndexBuffer();

         virtual void Bind() const;
         virtual void Unbind() const;

         virtual uint32_t GetCount() const override {return _count;}

      private:
         uint32_t _rendererId;
         uint32_t _count;

   };

}

#endif //CLAYENGINE_OPENGLBUFFER_H
