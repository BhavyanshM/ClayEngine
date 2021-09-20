//
// Created by quantum on 6/11/21.
//
#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "glm/glm.hpp"
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
         Application(const std::string& name = "Clay Engine");

         virtual ~Application();

         void Run();

         void OnEvent(Event& e);

         bool OnWindowClose(Event& e);

         bool OnWindowResize(WindowResizeEvent& e);

         void PushLayer(Layer* layer);

         void PushOverlay(Layer* layer);

         ImGuiLayer* GetImGuiLayer() {return _imguiLayer;}

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
