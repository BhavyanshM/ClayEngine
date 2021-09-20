//
// Created by quantum on 6/15/21.
//
#pragma once


#include "Core/Layer.h"
#include "imgui/imgui.h"

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


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

         void SetBlockEvents(bool block) { _blockEvents = block;}

      private:
         bool _blockEvents = true;
         float _time = 0.0f;

   };
}
