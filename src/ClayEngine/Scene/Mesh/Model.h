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
   class Model
   {
      public:
         Model() : _transformToParent(1.0f), _transformToWorld(1.0f), _color({1.0f, 1.0f, 1.0f, 1.0f}) {};

         void Update();
         virtual void Upload() = 0;
         virtual void Reset() = 0;

         Ref <VertexBuffer> GetVertexBuffer() const { return _vertexBuffer;}
         Ref <VertexArray> GetVertexArray() const { return _vertexArray;}
         const glm::mat4& GetTransformToParent() const { return _transformToParent;}
         const glm::mat4& GetTransformToWorld() const { return _transformToWorld;}
         const glm::vec4& GetColor() const { return _color;}
         RendererAPI::MODE GetType() const {return _type;}
         Ref <Shader> GetShader() const { return _shader;}

         void SetShader(const Ref <Shader>& shader){_shader = shader;}
         void SetColor(const glm::vec4& color){_color = color;}

         void RotateLocal(float angle, const glm::vec3& axis, bool radians = true);
         void RotateLocalX(float angle, bool radians = true);
         void RotateLocalY(float angle, bool radians = true);
         void RotateLocalZ(float angle, bool radians = true);
         void TranslateLocal(const glm::vec3& translation);

      protected:
         static const uint32_t MAX_POINTS = 400000;
         uint32_t _indices[MAX_POINTS];
         float _vertices[MAX_POINTS * 3];
         Ref <VertexArray> _vertexArray;
         Ref <IndexBuffer> _indexBuffer;
         Ref <VertexBuffer> _vertexBuffer;
         Ref <Shader> _shader;
         glm::mat4 _transformToParent;
         glm::mat4 _transformToWorld;
         RendererAPI::MODE _type;
         glm::vec4 _color;

         std::vector<Ref<Model>> children;
         Ref<Model> _parent;

   };
}

#endif //CLAYENGINE_MODEL_H
