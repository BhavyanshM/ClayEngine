//
// Created by quantum on 6/24/21.
//

#ifndef CLAYENGINE_ORTHOGRAPHICCAMERACONTROLLER_H
#define CLAYENGINE_ORTHOGRAPHICCAMERACONTROLLER_H

#include "Core/ClayHeaders.h"
#include "Renderer/CameraController.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace Clay {

   CameraController::CameraController(float aspectRatio, bool rotation)
         : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
   {
   }

   void CameraController::OnUpdate(Timestep ts)
   {
      CLAY_PROFILE_FUNCTION();
      if (Input::IsKeyPressed(Key::A))
      {
         m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
         m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
      }
      else if (Input::IsKeyPressed(Key::D))
      {
         m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
         m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
      }

      if (Input::IsKeyPressed(Key::W))
      {
         m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
         m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
      }
      else if (Input::IsKeyPressed(Key::S))
      {
         m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
         m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
      }

      if (m_Rotation)
      {
         if (Input::IsKeyPressed(Key::Q))
            m_CameraRotation += m_CameraRotationSpeed * ts;
         if (Input::IsKeyPressed(Key::E))
            m_CameraRotation -= m_CameraRotationSpeed * ts;

         if (m_CameraRotation > 180.0f)
            m_CameraRotation -= 360.0f;
         else if (m_CameraRotation <= -180.0f)
            m_CameraRotation += 360.0f;

         m_Camera.SetRotation(m_CameraRotation);
      }

      m_Camera.SetPosition(m_CameraPosition);

      m_CameraTranslationSpeed = m_ZoomLevel;
   }

   void CameraController::OnEvent(Event& e)
   {
      CLAY_PROFILE_FUNCTION();
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_CB(CameraController::OnMouseScrolled));
      dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_CB(CameraController::OnMouseScrolled));
      dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CB(CameraController::OnWindowResized));
   }

   void CameraController::OnResize(float width, float height)
   {
      CLAY_PROFILE_FUNCTION();
      m_AspectRatio = width / height;
      m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
   }

   bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
   {
      CLAY_PROFILE_FUNCTION();
      m_ZoomLevel -= e.GetOffsetY() * 0.25f;
      m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
      m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
      return false;
   }

   bool CameraController::OnWindowResized(WindowResizeEvent& e)
   {
      CLAY_PROFILE_FUNCTION();
      OnResize((float)e.GetWidth(), (float)e.GetHeight());
      return false;
   }

   bool CameraController::OnMouseMoved(MouseMovedEvent& e)
   {
      CLAY_PROFILE_FUNCTION();


   }

}
#endif //CLAYENGINE_ORTHOGRAPHICCAMERACONTROLLER_H
