//
// Created by quantum on 6/11/21.
//
#pragma once

#include "Log.h"
#include <iostream>
#include "GLFW/glfw3.h"

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Layer.h"
#include "Input.h"

#include "ImGui/ImGuiLayer.h"

#define BIND_EVENT_CB(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Clay
{
   class Application
   {
      public:
         Application();

         virtual ~Application();

         void Run();

         void OnEvent(Event& e);

         bool OnWindowClose(Event& e);

         void PushLayer(Layer* layer);

         void PushOverlay(Layer* layer);

         static Application& Get() { return *s_Instance; }

         Window& GetWindow() { return *_window; }

      private:
         static Application* s_Instance;
         LayerStack _layerStack;
         std::unique_ptr<Window> _window;
         bool _running;

         ImGuiLayer* _imguiLayer;

//         Application* CreateApplication();


   };


}
