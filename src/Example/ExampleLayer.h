//
// Created by quantum on 6/20/21.
//

#ifndef CLAYENGINE_EXAMPLELAYER_H
#define CLAYENGINE_EXAMPLELAYER_H

#include "Application.h"
#include "Clay.h"

   class ExampleLayer : public Clay::Layer
{
   public:
      ExampleLayer();
      ~ExampleLayer() = default;

      void OnAttach() override {};
      void OnDetach() override {};

      void OnUpdate() override;
      void OnEvent(Clay::Event& e) override;
      void OnImGuiRender() override;

      bool OnKeyPressedEvent(Clay::KeyPressedEvent& e);

   private:
      std::shared_ptr<Clay::VertexBuffer> _vertexBuffer;
      std::shared_ptr<Clay::IndexBuffer> _indexBuffer;
      std::shared_ptr<Clay::VertexArray> _vertexArray;

      std::shared_ptr<Clay::Shader> _shader;

      Clay::OrthographicCamera _camera;

      glm::vec3 _cameraPosition;
      float _cameraSpeed = 0.1f;
      float _cameraRotation = 0.0f;
};

#endif //CLAYENGINE_EXAMPLELAYER_H
