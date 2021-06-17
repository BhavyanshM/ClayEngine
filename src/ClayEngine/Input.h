//
// Created by quantum on 6/16/21.
//

#ifndef CLAYENGINE_INPUT_H
#define CLAYENGINE_INPUT_H

#include "Core.h"

namespace Clay
{
   class Input
   {
      public:
         inline static bool IsKeyPressed(int keyCode) {return s_Instance->IsKeyPressedImpl(keyCode);}
         inline static bool IsMouseButtonPressed(int button) {return s_Instance->IsMouseButtonPressedImpl(button);}
         inline static float GetMouseX() {return s_Instance->GetMouseXImpl();}
         inline static float GetMouseY() {return s_Instance->GetMouseYImpl();}

      protected:
         virtual bool IsKeyPressedImpl(int keyCode) = 0;
         virtual bool IsMouseButtonPressedImpl( int button) = 0;
         virtual float GetMouseXImpl() = 0;
         virtual float GetMouseYImpl() = 0;

      private:
         static Input* s_Instance;
   };
}

#endif //CLAYENGINE_INPUT_H
