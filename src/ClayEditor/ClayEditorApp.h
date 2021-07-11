//
// Created by quantum on 6/20/21.
//

#ifndef CLAYENGINE_CLAYEDITORAPP_H
#define CLAYENGINE_CLAYEDITORAPP_H

#include "Core/Application.h"
#include "Core/Clay.h"
#include "EditorLayer.h"

class ClayEditorApp : public Clay::Application
{
   public:
      ClayEditorApp();
      ~ClayEditorApp() = default;
};

#endif //CLAYENGINE_CLAYEDITORAPP_H
