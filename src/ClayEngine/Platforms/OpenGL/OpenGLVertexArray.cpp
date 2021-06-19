//
// Created by quantum on 6/18/21.
//

#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Clay
{
   static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:
            return GL_FLOAT;
         case ShaderDataType::Float2:
            return GL_FLOAT;
         case ShaderDataType::Float3:
            return GL_FLOAT;
         case ShaderDataType::Float4:
            return GL_FLOAT;
         case ShaderDataType::Mat3:
            return GL_FLOAT;
         case ShaderDataType::Mat4:
            return GL_FLOAT;
         case ShaderDataType::Int:
            return GL_INT;
         case ShaderDataType::Int2:
            return GL_INT;
         case ShaderDataType::Int3:
            return GL_INT;
         case ShaderDataType::Int4:
            return GL_INT;
         case ShaderDataType::Bool:
            return GL_BOOL;
      }
      CLAY_LOG_WARN("Unkown OpenGL Type.");
      return 0;
   }

   OpenGLVertexArray::OpenGLVertexArray()
   {
      glCreateBuffers(1, &_rendererId);
   }

   void OpenGLVertexArray::Bind()
   {
      glBindVertexArray(_rendererId);
   }

   void OpenGLVertexArray::Unbind()
   {
      glBindVertexArray(0);
   }

   void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
   {
      glBindVertexArray(_rendererId);
      vertexBuffer->Bind();

      uint32_t index = 0;
      const auto& layout = vertexBuffer->GetLayout();
      for (const auto& element : layout)
      {
         glEnableVertexAttribArray(index);
         glVertexAttribPointer(index, element.GetComponentCount(),
                               ShaderDataTypeToOpenGLBaseType(element.Type),
                               element.Normalized ? GL_TRUE : GL_FALSE,
                               layout.GetStride(), (const void *) element.Offset);
         index++;
      }
      _vertexBuffers.push_back(vertexBuffer);
   }

   void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
   {
      glBindVertexArray(_rendererId);
      indexBuffer->Bind();

      _indexBuffer = indexBuffer;
   }

   VertexArray *OpenGLVertexArray::Create()
   {
      return nullptr;
   }
}