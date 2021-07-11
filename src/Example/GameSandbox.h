//
// Created by quantum on 6/20/21.
//

#ifndef CLAYENGINE_CLAYEDITORAPP_H
#define CLAYENGINE_GAMESANDBOX_H

#include "Core/Application.h"
#include "Core/Clay.h"
#include "ExampleLayer.h"
#include "Example2D.h"

class ClayEditorApp : public Clay::Application
{
   public:
      ClayEditorApp()
         : Clay::Application("Hazel Editor")
      {
         PushLayer(new EditorLayer());
      }
      ~ClayEditorApp() = default;
};

#endif //CLAYENGINE_CLAYEDITORAPP_H
