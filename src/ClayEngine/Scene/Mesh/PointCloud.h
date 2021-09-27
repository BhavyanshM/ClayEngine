//
// Created by quantum on 9/24/21.
//

#ifndef CLAYENGINE_POINTCLOUD_H
#define CLAYENGINE_POINTCLOUD_H

#include "Core/ClayHeaders.h"
#include "Core/Core.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "glm/glm.hpp"

namespace Clay
{
   class PointCloud
   {
      public:
         PointCloud() = default;
         PointCloud(const std::string& filename, const glm::vec4& color);

         void Upload();
         void Reset();
         void Insert(float x, float y, float z);

         Ref<VertexBuffer> GetVertexBuffer() const { return _vertexBuffer;}
         Ref<VertexArray> GetVertexArray() const { return _vertexArray;}
         const glm::mat4& GetTransform() const { return _transform;}
         Ref<Shader> GetShader() const {return _shader;}
         void SetShader(const Ref<Shader>& shader) { _shader = shader;}
         void SetColor(const glm::vec4& color) {_color = color;}
         const glm::vec4& GetColor() const { return _color;}

         void RotateLocal(float angle, const glm::vec3& axis, bool radians = true);
         void RotateLocalX(float angle, bool radians = true);
         void RotateLocalY(float angle, bool radians = true);
         void RotateLocalZ(float angle, bool radians = true);

         void TranslateLocal(const glm::vec3& translation);

         uint32_t GetSize() const { return _index;}


      private:
         static const uint32_t MAX_POINTS = 400000;
         uint32_t _indices[MAX_POINTS];
         float _vertices[MAX_POINTS * 3];
         Ref<VertexArray> _vertexArray;
         Ref<IndexBuffer> _indexBuffer;
         Ref<VertexBuffer> _vertexBuffer;
         Ref<Shader> _shader;
         glm::mat4 _transform;
         glm::vec4 _color;
         uint32_t _index = 0;
   };
}

#endif //CLAYENGINE_POINTCLOUD_H
