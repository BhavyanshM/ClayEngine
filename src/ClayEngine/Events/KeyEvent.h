//
// Created by quantum on 6/12/21.
//

#ifndef CLAYENGINE_KEYEVENT_H
#define CLAYENGINE_KEYEVENT_H

#include "Event.h"

namespace Clay
{
   class KeyEvent : public Event
   {
      public:

      protected:
         KeyEvent(int keyCode) : _keyCode(keyCode)
         {
         }

         int _keyCode;
   };

   class KeyPressedEvent : public KeyEvent
   {
   };

   class KeyReleasedEvent : public KeyEvent
   {
   };
}

#endif //CLAYENGINE_KEYEVENT_H
