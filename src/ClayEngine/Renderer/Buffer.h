//
// Created by quantum on 6/17/21.
//

#ifndef CLAYENGINE_BUFFER_H
#define CLAYENGINE_BUFFER_H

#include "ClayHeaders.h"
#include "Log.h"


namespace Clay
{
   enum class ShaderDataType
   {
         None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
   };

   static uint32_t ShaderDataTypeSize(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:
            return 4;
         case ShaderDataType::Float2:
            return 4 * 2;
         case ShaderDataType::Float3:
            return 4 * 3;
         case ShaderDataType::Float4:
            return 4 * 4;
         case ShaderDataType::Mat3:
            return 4 * 3 * 3;
         case ShaderDataType::Mat4:
            return 4 * 4 * 4;
         case ShaderDataType::Int:
            return 4;
         case ShaderDataType::Int2:
            return 4 * 2;
         case ShaderDataType::Int3:
            return 4 * 3;
         case ShaderDataType::Int4:
            return 4 * 4;
         case ShaderDataType::Bool:
            return 1;
      }
      CLAY_LOG_WARN("Unkown Shader Type!");
      return 0;
   }

   struct BufferElement
   {
      std::string Name;
      ShaderDataType Type;
      uint32_t Size;
      uint32_t Offset;
      bool Normalized;

      BufferElement() {}

      BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Type(type), Normalized(normalized)
      {
      };

      uint32_t GetComponentCount() const
      {
         switch(Type)
         {
            case ShaderDataType::Float: return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Mat3: return 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4;
            case ShaderDataType::Int: return 1;
            case ShaderDataType::Int2: return 2;
            case ShaderDataType::Int3: return 3;
            case ShaderDataType::Int4: return 4;
            case ShaderDataType::Bool: return 1;
         }
      }
   };

   class BufferLayout
   {
      public:
         BufferLayout() {}

         BufferLayout(const std::initializer_list<BufferElement>& elements) : _elements(elements)
         {
            CalculateOffsetAndStride();
         }

         inline const std::vector<BufferElement>& GetElements() const
         {
            return _elements;
         }

         inline uint32_t GetStride() const
         {
            return _stride;
         }

         std::vector<BufferElement>::iterator begin() { return _elements.begin();}
         std::vector<BufferElement>::iterator end() { return _elements.end();}
         std::vector<BufferElement>::const_iterator begin() const { return _elements.begin();}
         std::vector<BufferElement>::const_iterator end() const { return _elements.end();}

      private:
         void CalculateOffsetAndStride()
         {
            uint32_t offset = 0;
            _stride = 0;
            for(auto& element : _elements)
            {
               element.Offset = offset;
               offset += element.Size;
               _stride += element.Size;
            }
         }

      private:
         std::vector<BufferElement> _elements;
         uint32_t _stride = 0;
   };

   class VertexBuffer
   {
      public:
         virtual ~VertexBuffer()
         {
         };

         virtual void Bind() const = 0;

         virtual void Unbind() const = 0;

         virtual uint32_t GetCount() const = 0;

         virtual void SetLayout(const BufferLayout& layout) = 0;

         virtual const BufferLayout& GetLayout() const = 0;

         static VertexBuffer *Create(float *vertices, uint32_t count);
   };

   class IndexBuffer
   {
      public:
         virtual ~IndexBuffer()
         {
         };

         virtual void Bind() const = 0;

         virtual void Unbind() const = 0;

         virtual uint32_t GetCount() const = 0;

         static IndexBuffer *Create(uint32_t *indices, uint32_t count);
   };
}

#endif //CLAYENGINE_BUFFER_H
