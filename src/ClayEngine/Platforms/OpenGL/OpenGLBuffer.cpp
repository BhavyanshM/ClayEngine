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

   OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
   {
      CLAY_PROFILE_FUNCTION();
      glCreateBuffers(1, &_rendererId);
      glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
      glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
   }

   OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t count) : _count(count)
   {
      CLAY_PROFILE_FUNCTION();
      glCreateBuffers(1, &_rendererId);
      glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
      glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * count, vertices, GL_STATIC_DRAW);
   }

   OpenGLVertexBuffer::~OpenGLVertexBuffer()
   {
      CLAY_PROFILE_FUNCTION();
      glDeleteBuffers(1, &_rendererId);
   }

   void OpenGLVertexBuffer::Bind() const
   {
      CLAY_PROFILE_FUNCTION();
      glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
   }

   void OpenGLVertexBuffer::Unbind() const
   {
      CLAY_PROFILE_FUNCTION();
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

   void OpenGLVertexBuffer::SetData(const void *data, uint32_t dataSize)
   {
      glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
      glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, data);
   }

   ///////////////////////////////////////////////////////////////////////
   // IndexBuffer /////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////

   OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : _count(count)
   {
      CLAY_PROFILE_FUNCTION();
      glCreateBuffers(1, &_rendererId);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
   }

   void OpenGLIndexBuffer::AddIndex(uint32_t index)
   {
      _pointIndices.emplace_back(index);
   }

   void OpenGLIndexBuffer::Upload(uint32_t count)
   {
      CLAY_PROFILE_FUNCTION();
      uint32_t totalIndices = (count == 0 ? _pointIndices.size() : count);
      _count = totalIndices;
      glCreateBuffers(1, &_rendererId);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndices *  sizeof(uint32_t), _pointIndices.data(), GL_STATIC_DRAW);
      _pointIndices.clear();
   }

   OpenGLIndexBuffer::~OpenGLIndexBuffer()
   {
      CLAY_PROFILE_FUNCTION();
      glDeleteBuffers(1, &_rendererId);
   }

   void OpenGLIndexBuffer::Bind() const
   {
      CLAY_PROFILE_FUNCTION();
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
   }

   void OpenGLIndexBuffer::Unbind() const
   {
      CLAY_PROFILE_FUNCTION();
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }

}
