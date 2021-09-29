//
// Created by quantum on 9/26/21.
//

#ifndef CLAYENGINE_MODEL_H
#define CLAYENGINE_MODEL_H

#include "Core/ClayHeaders.h"
#include "Core/Core.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"

namespace Clay
{
   class Mesh
   {
      public:
         Mesh(uint32_t count, RendererAPI::MODE type) : _color({1.0f, 1.0f, 1.0f, 1.0f}), _type(type)
         {
            MAX_POINTS = count;
         }
         uint32_t MAX_POINTS;
         uint32_t _index = 0;
         std::vector<float> _vertices;
         std::vector<uint32_t> _indices;
         RendererAPI::MODE _type;
         glm::vec4 _color;
         Ref <VertexArray> _vertexArray;
         Ref <IndexBuffer> _indexBuffer;
         Ref <VertexBuffer> _vertexBuffer;
         Ref <Shader> _shader;
   };

   class Model
   {
      public:
         Model() : _transformToParent(1.0f), _transformToWorld(1.0f) {_mesh = nullptr;};
         explicit Model(const Ref<Model>& parent, bool geometry = false, uint32_t count = 400000, RendererAPI::MODE type = RendererAPI::MODE::Points);

         void Update();
         virtual void Upload() {};
         virtual void Reset() {};

         Ref <VertexBuffer> GetVertexBuffer() const { return _mesh->_vertexBuffer;}
         Ref <VertexArray> GetVertexArray() const { return _mesh->_vertexArray;}
         Ref <IndexBuffer> GetIndexBuffer() const { return _mesh->_indexBuffer;}
         const glm::mat4& GetTransformToParent() const { return _transformToParent;}
         const glm::mat4& GetTransformToWorld() const { return _transformToWorld;}
         const glm::vec4& GetColor() const { return _mesh->_color;}
         RendererAPI::MODE GetType() const {return _mesh->_type;}
         Ref <Shader> GetShader() const { return _mesh->_shader;}
         uint32_t GetSize() const { return _mesh->_index;}


         void SetShader(const Ref <Shader>& shader){_mesh->_shader = shader;}
         void SetColor(const glm::vec4& color){_mesh->_color = color;}

         void RotateLocal(float angle, const glm::vec3& axis, bool radians = true);
         void RotateLocalX(float angle, bool radians = true);
         void RotateLocalY(float angle, bool radians = true);
         void RotateLocalZ(float angle, bool radians = true);
         void TranslateLocal(const glm::vec3& translation);

      protected:
         std::vector<Ref<Model>> children;
         glm::mat4 _transformToParent;
         glm::mat4 _transformToWorld;
         Ref<Model> _parent;
         Ref<Mesh> _mesh;

   };
}

#endif //CLAYENGINE_MODEL_H
