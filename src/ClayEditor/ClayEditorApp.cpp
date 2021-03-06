//
// Created by quantum on 6/20/21.
//

#include "ClayEditorApp.h"

ClayEditorApp::ClayEditorApp()
{
//   PushLayer(new ExampleLayer());
   PushLayer(new Clay::EditorLayer());
}

int main(int argc, char** argv)
{
   Clay::Log::Init();
   CLAY_LOG_INFO("Welcome to Clay Engine!");

   CLAY_PROFILE_BEGIN_SESSION("Startup", "ClayProfile-Startup.json");
   ClayEditorApp app;
   CLAY_PROFILE_END_SESSION();

   CLAY_PROFILE_BEGIN_SESSION("Runtime", "ClayProfile-Runtime.json");
   app.Run();
   CLAY_PROFILE_END_SESSION();

   return 0;
}