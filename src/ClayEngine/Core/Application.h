//
// Created by quantum on 6/11/21.
//
#pragma once

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

#include "glm.hpp"
#include "GLFW/glfw3.h"

#include "ClayHeaders.h"
#include "Clay.h"

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

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

         bool OnWindowResize(WindowResizeEvent& e);

         void PushLayer(Layer* layer);

         void PushOverlay(Layer* layer);

         static Application& Get() { return *s_Instance; }

         Window& GetWindow() { return *_window; }

         void Close();

      private:
         static Application* s_Instance;
         LayerStack _layerStack;
         std::unique_ptr<Window> _window;
         bool _running;
         bool _minimized;

         ImGuiLayer* _imguiLayer;

         double _lastFrameTime = 0.0f;



//         Application* CreateApplication();


   };


}
