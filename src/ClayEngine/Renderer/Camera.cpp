//
// Created by quantum on 6/19/21.
//

#include "Camera.h"
#include <glm/gtx/string_cast.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace Clay
{
   void Camera::SetOrthographic(float left, float right, float bottom, float top)
   {
      CLAY_PROFILE_FUNCTION();
      _type = CameraType::Orthographic;
      _ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
      _ViewMatrix = glm::mat4(1.0f);
      _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
   }

   void Camera::SetPerspective(float FOV, float aspect, float near, float far)
   {
      _type = CameraType::Perspective;
      _transform = glm::translate(glm::mat4(1.0f), {0,0,1}) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
      _ProjectionMatrix = glm::perspective(FOV, aspect, near, far);
      _ViewMatrix = glm::mat4(1.0f);
      _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
   }

   void Camera::SetProjection(float left, float right, float bottom, float top)
   {
      CLAY_PROFILE_FUNCTION();
      _ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
      _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
   }

   void Camera::RecalculateViewMatrix()
   {
      CLAY_PROFILE_FUNCTION();

      _ViewMatrix = glm::inverse(_transform);
      _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
      CLAY_LOG_INFO("Transform: {}", glm::to_string(_transform));
   }

   void Camera::RotateLocal(float angle, const glm::vec3& axis, bool radians)
   {
      _transform = glm::rotate(glm::mat4(1.0f), angle, axis) * _transform;
      RecalculateViewMatrix();
   }

   void Camera::RotateLocalX(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(1.0f,0.0f,0.0f), radians);
   }

   void Camera::RotateLocalY(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(0,1,0), radians);
   }

   void Camera::RotateLocalZ(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(0,0,1), radians);
   }

   void Camera::TranslateLocal(const glm::vec3& translation)
   {
//      _transform = glm::transpose(glm::translate(glm::mat4(1.0f), translation)) * _transform;

      _transform[0][3] += translation[0];
      _transform[1][3] += translation[1];
      _transform[2][3] += translation[2];

      RecalculateViewMatrix();
   }
}