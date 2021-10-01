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
      m_Model->SetTransformToWorld(glm::translate(glm::mat4(1.0f), {0,0,1}) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1)));
      _ProjectionMatrix = glm::perspective(FOV, aspect, near, far);
      _ViewMatrix = glm::inverse(m_Model->GetTransformToWorld());
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

      _ViewMatrix = glm::inverse(m_Model->GetTransformToParent());
      _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
//      CLAY_LOG_INFO("Transform: {}", glm::to_string(m_Model->GetTransformToParent()));
   }

   void Camera::RotateLocal(float angle, const glm::vec3& axis, bool radians)
   {
      m_Model->RotateLocal(angle, axis, radians);
      RecalculateViewMatrix();
   }

   void Camera::RotateLocalX(float angle, bool radians)
   {
      m_Model->RotateLocalX(angle, radians);
      RecalculateViewMatrix();
   }

   void Camera::RotateLocalY(float angle, bool radians)
   {
      m_Model->RotateLocalY(angle, radians);
      RecalculateViewMatrix();
   }

   void Camera::RotateLocalZ(float angle, bool radians)
   {
      m_Model->RotateLocalZ(angle, radians);
      RecalculateViewMatrix();
   }

   void Camera::TranslateLocal(const glm::vec3& translation)
   {
      m_Model->TranslateLocal(translation);
      RecalculateViewMatrix();
   }
}