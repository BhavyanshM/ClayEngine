//
// Created by quantum on 6/19/21.
//

#ifndef CLAYENGINE_CAMERA_H
#define CLAYENGINE_CAMERA_H

#include "Core/Core.h"
#include "glm/glm.hpp"

namespace Clay
{

   enum CameraType
   {
      Perspective, Orthographic
   };

   class Camera
   {
      public:
         Camera(float left, float right, float bottom, float top);

         void SetPosition(const glm::vec3& position) { _Position = position; RecalculateViewMatrix();}
         void SetRotation(float rotation) {_Rotation = rotation; RecalculateViewMatrix();}

         void SetProjection(float left, float right, float bottom, float top);

         const glm::vec3& GetPosition() const { return _Position; }
         float GetRotation() const { return _Rotation; }

         const glm::mat4& GetProjectionMatrix() const { return _ProjectionMatrix; }
         const glm::mat4& GetViewMatrix() const { return _ViewMatrix; }
         const glm::mat4& GetViewProjectionMatrix() const { return _ViewProjectionMatrix; }

         CameraType GetCameraType() {return _type;}

      private:
         void RecalculateViewMatrix();

      private:
         CameraType _type;
         glm::mat4 _ProjectionMatrix;
         glm::mat4 _ViewMatrix;
         glm::mat4 _ViewProjectionMatrix;

         glm::vec3 _Position;
         float _Rotation = 0.0f;

   };

}

#endif //CLAYENGINE_CAMERA_H
