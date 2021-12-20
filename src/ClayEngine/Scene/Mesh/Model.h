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
         uint32_t _cummulativeIndexCount = 0;
         std::vector<float> _vertices;
         std::vector<uint32_t> _indices;
         std::vector<glm::vec4> _colors;
         RendererAPI::MODE _type;
         glm::vec4 _color;
         Ref <Shader> _shader;
         std::vector<int> _partIds;
   };

   class Model : public std::enable_shared_from_this<Model>
   {
      public:
         Model() : _transformToParent(1.0f), _transformToWorld(1.0f) {_mesh = nullptr;};
         explicit Model(const Ref<Model>& parent, bool geometry = false, uint32_t count = 400000, RendererAPI::MODE type = RendererAPI::MODE::Points);

         void Update();
         virtual void Load(const std::string& filename) {};
         virtual void Reset() {};
         virtual void Print() {};
         virtual void InsertVertex(float x, float y, float z) {};
         virtual void InsertIndex(uint32_t index) {};
         virtual void AddMesh(const Ref<Model>& model);

         Ref <Model> GetParent() const { return _parent;}
         const glm::mat4& GetTransformToParent() const { return _transformToParent;}
         const glm::mat4& GetTransformToWorld() const { return _transformToWorld;}
         void SetTransformToWorld(const glm::mat4& transform) {_transformToWorld = transform;}
         void SetTransformToParent(const glm::mat4& transform) {_transformToParent = transform;}
         const glm::vec4& GetColor() const { return _mesh->_color;}
         RendererAPI::MODE GetType() const {return _mesh->_type;}
         Ref <Shader> GetShader() const { return _mesh->_shader;}
         uint32_t GetSize() const { return _mesh->_index;}
         uint32_t GetPreviousIndexCount() const { return _mesh->_cummulativeIndexCount;}
         Ref<Mesh> GetMesh() const { return _mesh; }
         std::vector<glm::vec4> GetColors() const { return _mesh->_colors; }

         void AddChild(Ref<Model> child) {children.emplace_back(child);}
         void SetShader(const Ref <Shader>& shader){_mesh->_shader = shader;}
         void SetColor(const glm::vec4& color){_mesh->_color = color;}
         void InsertColor(const glm::vec4& color) {_mesh->_colors.emplace_back(color); };
         void SetPartIds(const std::vector<int>& partIds) {_mesh->_partIds = partIds;}
         void ResetIndexCount() { _mesh->_cummulativeIndexCount = _mesh->_index; };

         void RotateLocal(float angle, const glm::vec3& axis, bool radians = true);
         void RotateLocalX(float angle, bool radians = true);
         void RotateLocalY(float angle, bool radians = true);
         void RotateLocalZ(float angle, bool radians = true);
         void TranslateLocal(const glm::vec3& translation);
         void TransformLocal(const glm::mat4& transform);
         void TransformGlobal(const glm::mat4& transform);
         void ApplyTransform(const glm::vec3& angles, const glm::vec3& translation);
         void ApplyTransform(const glm::mat4& transform);

      protected:
         std::vector<Ref<Model>> children;
         glm::mat4 _transformToParent;
         glm::mat4 _transformToWorld;
         Ref<Model> _parent;
         Ref<Mesh> _mesh;

   };
}

#endif //CLAYENGINE_MODEL_H
