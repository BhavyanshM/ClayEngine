//
// Created by quantum on 6/17/21.
//

#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace Clay
{
   ///////////////////////////////////////////////////////////////////////
   // VertexBuffer ///////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////

   OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t count) : _count(count)
   {
      glCreateBuffers(1, &_rendererId);
      glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
      glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
   }

   OpenGLVertexBuffer::~OpenGLVertexBuffer()
   {
      glDeleteBuffers(1, &_rendererId);
   }

   void OpenGLVertexBuffer::Bind() const
   {
      glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
   }

   void OpenGLVertexBuffer::Unbind() const
   {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   const BufferLayout& OpenGLVertexBuffer::GetLayout() const
   {
      return _layout;
   }

   void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
   {
      _layout = layout;
   }

   ///////////////////////////////////////////////////////////////////////
   // IndexBuffer /////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////

   OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : _count(count)
   {
      glCreateBuffers(1, &_rendererId);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
   }

   OpenGLIndexBuffer::~OpenGLIndexBuffer()
   {
      glDeleteBuffers(1, &_rendererId);
   }

   void OpenGLIndexBuffer::Bind() const
   {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
   }

   void OpenGLIndexBuffer::Unbind() const
   {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }
}
