//
// Created by quantum on 6/16/21.
//

#include "LinuxInput.h"

#include "Core/Application.h"

namespace Clay
{
   Input* Input::s_Instance = new LinuxInput();

   bool LinuxInput::IsKeyPressedImpl(int keyCode)
   {
      auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

      auto state = glfwGetKey(window, keyCode);

      return state == GLFW_PRESS || state == GLFW_REPEAT;
   }

   bool LinuxInput::IsMouseButtonPressedImpl(int button)
   {
      auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

      auto state = glfwGetMouseButton(window, button);

      return state == GLFW_PRESS;
   }

   float LinuxInput::GetMouseXImpl()
   {
      auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);

      return (float)xpos;
   }

   float LinuxInput::GetMouseYImpl()
   {
      auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);

      return (float)ypos;
   }
}
