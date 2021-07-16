//
// Created by quantum on 6/29/21.
//

#ifndef CLAYENGINE_EDITORLAYER_H
#define CLAYENGINE_EDITORLAYER_H

#include "Core/Application.h"
#include "Core/Clay.h"

namespace Clay
{
   class EditorLayer : public Layer
   {
      public:
         EditorLayer();

         ~EditorLayer() = default;

         void OnAttach() override;

         void OnDetach() override;

         void OnUpdate(Timestep ts) override;

         void OnEvent(Event& e) override;

         void OnImGuiRender() override;

      private:
         Ref<FrameBuffer> _frameBuffer;

         Ref<Shader> _shader;

         CameraController _cameraController;

         glm::vec4 _squareColor;

         Ref<Texture2D> _texture;

         struct ProfileResult
         {
            const char *Name;
            float Time;
         };

         std::vector<ProfileResult> _profileResults;

         glm::vec2 _viewportSize = {0,0};

         bool _viewportFocused = false;
         bool _viewportHovered = false;
   };
}
#endif //CLAYENGINE_EDITORLAYER_H
