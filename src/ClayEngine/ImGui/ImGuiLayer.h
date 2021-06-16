//
// Created by quantum on 6/15/21.
//
#pragma once


#include "Layer.h"
#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


namespace Clay
{
   class ImGuiLayer : public Layer
   {
      public:
         ImGuiLayer();
         ~ImGuiLayer();

         void OnAttach() override;
         void OnDetach() override;
         void OnEvent(Event& e) override;

         void OnImGuiRender() override;

         void Begin();
         void End();

         void BlockEvents(bool block) { _blockEvents = block; }

         void SetDarkThemeColors();

      private:
         bool _blockEvents = true;
         float _time = 0.0f;

   };
}
