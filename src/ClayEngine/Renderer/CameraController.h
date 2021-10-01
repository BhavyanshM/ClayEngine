#include "Renderer/Camera.h"
#include "Core/Timestep.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"


namespace Clay {

   class CameraController
   {
      public:
         CameraController() = default;
         CameraController(float aspectRatio, Ref<Model> cameraModel, bool rotation = false);

         void OnUpdate(Timestep ts);
         void OnEvent(Event& e);

         void OnResize(float width, float height);

         Camera& GetCamera() { return m_Camera; }
         const Camera& GetCamera() const { return m_Camera; }

         float GetZoomLevel() const { return m_ZoomLevel; }
         void SetZoomLevel(float level) { m_ZoomLevel = level; }
         void SetAspectRatio(float aspectRatio) {m_AspectRatio = aspectRatio;}

      private:
         bool OnMouseScrolled(MouseScrolledEvent& e);
         bool OnWindowResized(WindowResizeEvent& e);
         bool OnMouseMoved(MouseMovedEvent& e);
         bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
         bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
      private:
         float _lastX = 0;
         float _lastY = 0;
         float m_AspectRatio;
         float m_ZoomLevel = 1.0f;
         Camera m_Camera;


         bool _mouseLeftButtonPressed = false;
         bool _mouseRightButtonPressed = false;
         bool _mouseMiddleButtonPressed = false;
         bool _firstClick = false;

         glm::vec3 m_CameraOrigin = {0.0f, 0.0f, 0.0f};

         float m_CameraTranslationSpeed = 15.0f, m_CameraRotationSpeed = 180.0f;
   };

}