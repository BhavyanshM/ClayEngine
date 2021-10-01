//
// Created by quantum on 6/19/21.
//

#ifndef CLAYENGINE_CAMERA_H
#define CLAYENGINE_CAMERA_H

#include "Core/Core.h"
#include "glm/glm.hpp"
#include "Scene/Mesh/Model.h"

namespace Clay
{

   enum CameraType
   {
      Perspective, Orthographic
   };

   class Camera
   {
      public:
         Camera() = default;

         void SetPerspective(float FOV, float aspect, float near, float far);
         void SetOrthographic(float left, float right, float bottom, float top);

         void RotateLocal(float angle, const glm::vec3& axis, bool radians = true);
         void RotateLocalX(float angle, bool radians = true);
         void RotateLocalY(float angle, bool radians = true);
         void RotateLocalZ(float angle, bool radians = true);

         void TranslateLocal(const glm::vec3& translation);


         void SetProjection(float left, float right, float bottom, float top);

         const glm::mat4& GetProjectionMatrix() const { return _ProjectionMatrix; }
         const glm::mat4& GetViewMatrix() const { return _ViewMatrix; }
         const glm::mat4& GetViewProjectionMatrix() const { return _ViewProjectionMatrix; }

         CameraType GetCameraType() {return _type;}
         Ref<Model> GetModel() const {return m_Model;}
         void SetModel(Ref<Model> model) { m_Model = model;}

      private:
         void RecalculateViewMatrix();

      private:
         CameraType _type;
         glm::mat4 _ProjectionMatrix;
         glm::mat4 _ViewMatrix;
         glm::mat4 _ViewProjectionMatrix;

         Ref<Model> m_Model;

   };

}

#endif //CLAYENGINE_CAMERA_H
