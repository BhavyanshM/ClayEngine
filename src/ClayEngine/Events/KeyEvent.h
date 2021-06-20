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
         KeyCode GetKeyCode() const { return _keyCode; }
         EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard);

      protected:
         KeyEvent(const KeyCode keyCode) : _keyCode(keyCode)
         {
         }

         KeyCode _keyCode;
   };

   class KeyPressedEvent : public KeyEvent
   {
      public:
         KeyPressedEvent(const KeyCode keyCode, int repeatCount) : KeyEvent(keyCode), _repeatCount(repeatCount) {}

         inline int GetRepeatCount() const {return _repeatCount;}

         std::string toString() const override
         {
            std::stringstream ss;
            ss << "KeyPressedEvent: [KeyCode:" << _keyCode << ", RepeatCount:" << _repeatCount << "]" << std::endl;
            return ss.str();
         }

         EVENT_CLASS_TYPE(KeyPressed)

      private:
         int _repeatCount;
   };

   class KeyReleasedEvent : public KeyEvent
   {
      public:
         KeyReleasedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

         std::string toString() const override
         {
            std::stringstream ss;
            ss << "KeyReleasedEvent: [KeyCode:" << _keyCode << "]" << std::endl;
            return ss.str();
         }

         EVENT_CLASS_TYPE(KeyReleased)
   };
}

#endif //CLAYENGINE_KEYEVENT_H
