//
// Created by quantum on 9/26/21.
//

#include "Model.h"

namespace Clay {

   Model::Model(const Ref<Model>& parent, bool geometry, uint32_t count, RendererAPI::MODE type) : _transformToParent(1.0f)
   {
      if(parent == nullptr)
      {
         _transformToWorld = glm::mat4(1.0f);
      }
      else
      {
         _parent = parent;
         _transformToWorld = parent->GetTransformToWorld();
         _parent->AddChild(std::shared_ptr<Model>(this));
      }
      if(geometry) {
         _mesh = std::make_shared<Mesh>(count, type);
      }
      else
      {
         _mesh = nullptr;
      }
   }

   void Model::RotateLocal(float angle, const glm::vec3& axis, bool radians)
   {
      _transformToParent = glm::rotate(glm::mat4(1.0f), angle, axis) * _transformToParent;
      Update();
   }

   void Model::RotateLocalX(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(1.0f,0.0f,0.0f), radians);
      Update();
   }

   void Model::RotateLocalY(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(0,1,0), radians);
      Update();
   }

   void Model::RotateLocalZ(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(0,0,1), radians);
      Update();
   }

   void Model::TranslateLocal(const glm::vec3& translation)
   {
      _transformToParent[3][0] += translation[0];
      _transformToParent[3][1] += translation[1];
      _transformToParent[3][2] += translation[2];
      Update();
   }

   void Model::TransformLocal(const glm::mat4& transform)
   {
      _transformToParent = _transformToParent * transform;
   }

   void Model::TransformGlobal(const glm::mat4& transform)
   {
      _transformToWorld = _transformToWorld * transform;
   }

   void Model::Update()
   {
      if(_parent != nullptr)
         _transformToWorld = _parent->GetTransformToWorld() * _transformToParent;

      for(Ref<Model> model : children)
         model->Update();
   }

   void Model::AddMesh(const Ref<Model>& model)
   {
      for(int i = 0; i<model->GetSize(); i++)
      {
         InsertVertex(model->GetMesh()->_vertices[i*3+0],
                      model->GetMesh()->_vertices[i*3+1],
                      model->GetMesh()->_vertices[i*3+2]);
         SetColor(model->GetColor());
      }
      for(int i = 0; i<model->GetMesh()->_indices.size(); i++){
         InsertIndex(model->GetMesh()->_indices[i]);
      }

      if(model->GetColors().size() != 0)
      {
         for (int i = 0; i<model->GetColors().size(); i++) InsertColor(model->GetColors()[i]);
      }

      ResetIndexCount();
   }

   void Model::ApplyTransform(const glm::vec3& angles, const glm::vec3& translation)
   {
      glm::mat4 transform =   glm::rotate(glm::mat4(1.0f), angles.z, {0.0, 0.0, 1.0}) *
                              glm::rotate(glm::mat4(1.0f), angles.y, {0.0, 1.0, 0.0}) *
                              glm::rotate(glm::mat4(1.0f), angles.x, {1.0, 0.0, 0.0});
      glm::vec4 point;
      for(int i = 0; i<GetSize(); i++)
      {
         point = transform * glm::vec4(GetMesh()->_vertices[i*3 + 0],
                                       GetMesh()->_vertices[i*3 + 1],
                                       GetMesh()->_vertices[i*3 + 2], 1);
         _mesh->_vertices[i*3 + 0] = point.x + translation.x;
         _mesh->_vertices[i*3 + 1] = point.y + translation.y;
         _mesh->_vertices[i*3 + 2] = point.z + translation.z;
      }
   }

   void Model::ApplyTransform(const glm::mat4& transform)
   {
      glm::vec4 point;
      for(int i = 0; i<GetSize(); i++)
      {
         point = transform * glm::vec4(GetMesh()->_vertices[i*3 + 0],
                                       GetMesh()->_vertices[i*3 + 1],
                                       GetMesh()->_vertices[i*3 + 2], 1);
         _mesh->_vertices[i*3 + 0] = point.x;
         _mesh->_vertices[i*3 + 1] = point.y;
         _mesh->_vertices[i*3 + 2] = point.z;
      }
   }
}