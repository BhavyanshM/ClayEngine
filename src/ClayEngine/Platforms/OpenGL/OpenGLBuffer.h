//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_OPENGLBUFFER_H
#define CLAYENGINE_OPENGLBUFFER_H

#include "Core/ClayHeaders.h"
#include "Renderer/Buffer.h"

namespace Clay
{
   class OpenGLVertexBuffer : public VertexBuffer
   {
      public:
         explicit OpenGLVertexBuffer(uint32_t count);
         OpenGLVertexBuffer(float* vertices, uint32_t count);
         virtual ~OpenGLVertexBuffer();

         virtual void Bind() const override;
         virtual void Unbind() const override;

         virtual const BufferLayout& GetLayout() const override;
         virtual void SetLayout(const BufferLayout& layout) override;
         virtual void SetData(const void* data, uint32_t dataSize) override;

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
         OpenGLIndexBuffer(){};
         virtual ~OpenGLIndexBuffer();

         virtual void Bind() const;
         virtual void Unbind() const;
         virtual void Upload(uint32_t count = 0);
         virtual void AddIndex(uint32_t index);



         virtual uint32_t GetCount() const override {return _count;}

      private:
         uint32_t _rendererId;
         uint32_t _count;

   };

}

#endif //CLAYENGINE_OPENGLBUFFER_H
