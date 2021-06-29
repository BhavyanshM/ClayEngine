//
// Created by quantum on 6/20/21.
//

#include "GameSandbox.h"

GameSandbox::GameSandbox()
{
//   PushLayer(new ExampleLayer());
   PushLayer(new Example2D());
}

int main()
{
   Clay::Log::Init();
   CLAY_LOG_INFO("Welcome to Clay Engine!");

   GameSandbox app;
   app.Run();

   return 0;
}