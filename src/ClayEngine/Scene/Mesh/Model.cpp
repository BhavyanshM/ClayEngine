//
// Created by quantum on 9/26/21.
//

#include "Model.h"

namespace Clay {

   Model::Model(const Ref<Model>& parent) : _transformToParent(1.0f), _color({0.3f, 7.0f, 0.2f, 1.0f})
   {
      if(parent == nullptr)
      {
         _transformToWorld = glm::mat4(1.0f);
      }
      else
      {
         _parent = parent;
         _transformToWorld = parent->GetTransformToWorld();
      }
   }

   void Model::RotateLocal(float angle, const glm::vec3& axis, bool radians)
   {
      _transformToParent = glm::rotate(glm::mat4(1.0f), angle, axis) * _transformToParent;
   }

   void Model::RotateLocalX(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(1.0f,0.0f,0.0f), radians);
   }

   void Model::RotateLocalY(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(0,1,0), radians);
   }

   void Model::RotateLocalZ(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(0,0,1), radians);
   }

   void Model::TranslateLocal(const glm::vec3& translation)
   {
      //      _transformToParent = glm::transpose(glm::translate(glm::mat4(1.0f), translation)) * _transformToParent;

      _transformToParent[3][0] += translation[0];
      _transformToParent[3][1] += translation[1];
      _transformToParent[3][2] += translation[2];
   }

   void Model::Update()
   {
      if(_parent != nullptr)
         _transformToWorld = _parent->GetTransformToWorld() * _transformToParent;

      for(Ref<Model> model : children)
         model->Update();
   }
}