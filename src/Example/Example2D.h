//
// Created by quantum on 6/29/21.
//

#ifndef CLAYENGINE_EXAMPLE2D_H
#define CLAYENGINE_EXAMPLE2D_H

#include "Core/Application.h"
#include "Core/Clay.h"

class Example2D : public Clay::Layer
{
   public:
      Example2D();
      ~Example2D() = default;

      void OnAttach() override;
      void OnDetach() override;

      void OnUpdate(Clay::Timestep ts) override;
      void OnEvent(Clay::Event& e) override;
      void OnImGuiRender() override;

   private:
      Clay::Ref<Clay::VertexBuffer> _vertexBuffer;
      Clay::Ref<Clay::IndexBuffer> _indexBuffer;
      Clay::Ref<Clay::VertexArray> _vertexArray;
      Clay::Ref<Clay::FrameBuffer> _frameBuffer;

      Clay::Ref<Clay::Shader> _shader;

      Clay::OrthographicCameraController _cameraController;

      glm::vec4 _squareColor;




};

#endif //CLAYENGINE_EXAMPLE2D_H
