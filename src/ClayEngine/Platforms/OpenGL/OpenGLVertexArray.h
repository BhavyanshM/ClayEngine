//
// Created by quantum on 6/18/21.
//

#ifndef CLAYENGINE_OPENGLVERTEXARRAY_H
#define CLAYENGINE_OPENGLVERTEXARRAY_H


#include "Renderer/VertexArray.h"

namespace Clay
{
   class OpenGLVertexArray : public VertexArray
   {
      public:
         OpenGLVertexArray();
         ~OpenGLVertexArray() override;

         virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
         virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

         virtual const Ref<IndexBuffer>& GetIndexBuffer() const override {return _indexBuffer;};

         virtual void Bind() override;
         virtual void Unbind() override;

         static VertexArray* Create();

      private:
         std::vector<Ref<VertexBuffer>> _vertexBuffers;
         Ref<IndexBuffer> _indexBuffer;
         uint32_t _rendererId;
   };

}
#endif //CLAYENGINE_OPENGLVERTEXARRAY_H
