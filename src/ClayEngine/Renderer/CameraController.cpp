//
// Created by quantum on 6/24/21.
//

#ifndef CLAYENGINE_ORTHOGRAPHICCAMERACONTROLLER_H
#define CLAYENGINE_ORTHOGRAPHICCAMERACONTROLLER_H

#include "Core/ClayHeaders.h"
#include "Renderer/CameraController.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace Clay
{

   CameraController::CameraController(float aspectRatio, bool rotation) : m_AspectRatio(aspectRatio)
   {
      m_Camera.SetPerspective(glm::radians(80.0f), m_AspectRatio, 0.01f, 1000.0f);
      m_Camera.TranslateLocal({0.0f, 0.0f, 1.0f});
   }

   void CameraController::OnUpdate(Timestep ts)
   {
      CLAY_PROFILE_FUNCTION();
   }

   void CameraController::OnEvent(Event& e)
   {
      CLAY_PROFILE_FUNCTION();
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_CB(CameraController::OnMouseMoved));
      dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_CB(CameraController::OnMouseScrolled));
      dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CB(CameraController::OnWindowResized));
      dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_CB(CameraController::OnMouseButtonPressed));
      dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_CB(CameraController::OnMouseButtonReleased));
   }

   void CameraController::OnResize(float width, float height)
   {
      CLAY_PROFILE_FUNCTION();
      m_AspectRatio = width / height;
      m_Camera.SetPerspective(glm::radians(80.0f), m_AspectRatio, 0.01f, 1000.0f);
   }

   bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
   {
      CLAY_PROFILE_FUNCTION();
      m_Camera.TranslateLocal({0.0f, 0.0f, e.GetOffsetY() * 0.1f});
      return false;
   }

   bool CameraController::OnWindowResized(WindowResizeEvent& e)
   {
      CLAY_PROFILE_FUNCTION();
      OnResize((float) e.GetWidth(), (float) e.GetHeight());
      return false;
   }

   bool CameraController::OnMouseMoved(MouseMovedEvent& e)
   {
      CLAY_PROFILE_FUNCTION();

      if (_firstClick && _mouseLeftButtonPressed)
      {
         _lastX = e.GetX();
         _lastY = e.GetY();
         _firstClick = false;
      }
      else if (_mouseLeftButtonPressed)
      {
         m_Camera.RotateLocalY(0.01f * (_lastX - e.GetX()), true);
         _lastX = e.GetX();
         _lastY = e.GetY();
      }

      return false;
   }

   bool CameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
   {
      CLAY_PROFILE_FUNCTION();

      _mouseLeftButtonPressed = true;
      _firstClick = true;

      return false;
   }

   bool CameraController::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
   {
      CLAY_PROFILE_FUNCTION();

      _mouseLeftButtonPressed = false;

      return false;
   }
}
#endif //CLAYENGINE_ORTHOGRAPHICCAMERACONTROLLER_H
