//
// Created by quantum on 6/16/21.
//

#ifndef CLAYENGINE_LINUXINPUT_H
#define CLAYENGINE_LINUXINPUT_H

#include "Core/Input.h"

namespace Clay
{
   class LinuxInput : public Input
   {
      public:
         virtual bool IsKeyPressedImpl(int keyCode) override;
         virtual bool IsMouseButtonPressedImpl( int button) override;
         virtual float GetMouseXImpl() override;
         virtual float GetMouseYImpl() override;
   };

}

#endif //CLAYENGINE_LINUXINPUT_H
