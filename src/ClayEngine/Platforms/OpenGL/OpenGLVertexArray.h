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
         virtual ~OpenGLVertexArray() {}

         virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
         virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
         virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

         virtual void Bind() override;
         virtual void Unbind() override;

         static VertexArray* Create();

      private:
         std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
         std::shared_ptr<IndexBuffer> _indexBuffer;
         uint32_t _rendererId;
   };

}
#endif //CLAYENGINE_OPENGLVERTEXARRAY_H
