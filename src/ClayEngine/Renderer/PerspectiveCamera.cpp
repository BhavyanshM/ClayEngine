//
// Created by quantum on 6/19/21.
//

#include "PerspectiveCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Clay
{
   PerspectiveCamera::PerspectiveCamera(float fovY, float aspect, float zNear, float zFar) : _ProjectionMatrix(
         glm::perspective(fovY, aspect, zNear, zFar)), _ViewMatrix(1.0f)
   {
      CLAY_PROFILE_FUNCTION();
      _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
   }

   void PerspectiveCamera::SetProjection(float fovY, float aspect, float zNear, float zFar)
   {
      CLAY_PROFILE_FUNCTION();
      _ProjectionMatrix = glm::perspective(fovY, aspect, zNear, zFar);
      _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
   }

   void PerspectiveCamera::RecalculateViewMatrix()
   {
      CLAY_PROFILE_FUNCTION();
      glm::mat4 transform = glm::translate(glm::mat4(1.0f), _Position) * glm::rotate(glm::mat4(1.0f), _Rotation, glm::vec3(0, 0, 1));
      _ViewMatrix = glm::inverse(transform);
      _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
   }
}