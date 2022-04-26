//
// Created by quantum on 6/29/21.
//

#ifndef CLAYENGINE_EDITORLAYER_H
#define CLAYENGINE_EDITORLAYER_H

#include "Core/Application.h"
#include "Core/Clay.h"
#include "Core/ClayHeaders.h"
#include "Scene/Mesh/TriangleMesh.h"
#include "ImGui/FileBrowserUI.h"

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

         std::vector<Ref<Model>> _models;
         Ref<Model> _rootPCL;

         Ref<TriangleMesh> cylinder;


         struct ProfileResult
         {
            const char *Name;
            float Time;
         };

         std::vector<ProfileResult> _profileResults;

         glm::vec2 _viewportSize = {0,0};
         float _currentTime = 0.0f;
         uint32_t _frameCount = 0;

         bool _viewportFocused = false;
         bool _viewportHovered = false;
         bool _animationEnabled = false;

         int _lineWidth = 2;
         int _pointSize = 2;

         FileBrowserUI fileBrowserUI;
         std::string selectedPath;

         bool showFileBrowser = false;
   };


}
#endif //CLAYENGINE_EDITORLAYER_H
