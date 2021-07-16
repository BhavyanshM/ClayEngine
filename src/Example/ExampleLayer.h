//
// Created by quantum on 6/20/21.
//

#ifndef CLAYENGINE_EXAMPLELAYER_H
#define CLAYENGINE_EXAMPLELAYER_H

#include "Core/Application.h"
#include "Core/Clay.h"

   class ExampleLayer : public Clay::Layer
{
   public:
      ExampleLayer();
      ~ExampleLayer() = default;

      void OnAttach() override;
      void OnDetach() override;

      void OnUpdate(Clay::Timestep ts) override;
      void OnEvent(Clay::Event& e) override;
      void OnImGuiRender() override;

      bool OnKeyPressedEvent(Clay::KeyPressedEvent& e);

   private:
      Clay::Ref<Clay::VertexBuffer> _vertexBuffer;
      Clay::Ref<Clay::IndexBuffer> _indexBuffer;
      Clay::Ref<Clay::VertexArray> _vertexArray;
      Clay::Ref<Clay::Texture2D> _texture;
      Clay::Ref<Clay::FrameBuffer> _frameBuffer;

      Clay::Ref<Clay::Shader> _shader;

      Clay::CameraController _cameraController;

      glm::vec4 _squareColor;

};

#endif //CLAYENGINE_EXAMPLELAYER_H
