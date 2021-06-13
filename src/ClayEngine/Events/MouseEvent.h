//
// Created by quantum on 6/12/21.
//

#ifndef CLAYENGINE_MOUSEEVENT_H
#define CLAYENGINE_MOUSEEVENT_H

#include "Event.h"

namespace Clay
{
   class MouseMovedEvent : public Event
   {
      public:
         MouseMovedEvent(float x, float y) : _mouseX(x), _mouseY(y) {}

         inline float GetX() const { return _mouseX; }
         inline float GetY() const { return _mouseY; }

         std::string toString() const override
         {
            std::stringstream ss;
            ss << "MouseMovedEvent: [mouseX: " << _mouseX << ", mouseY:" << _mouseY << "]" << std::endl;
            return ss.str();
         }

         EVENT_CLASS_TYPE(MouseMoved)
         EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

      private:
         float _mouseX, _mouseY;
   };

   class MouseScrolledEvent : public Event
   {
      public:
         MouseScrolledEvent(float x, float y) : _offsetX(x), _offsetY(y) {}

         inline float GetOffsetX() const { return _offsetX; }
         inline float GetOffsetY() const { return _offsetY; }

         std::string toString() const override
         {
            std::stringstream ss;
            ss << "MouseScrolledEvent: [mouseX: " << _offsetX << ", mouseY:" << _offsetY << "]" << std::endl;
            return ss.str();
         }

         EVENT_CLASS_TYPE(MouseScrolled)
         EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

      private:
         float _offsetX, _offsetY;
   };

   class MouseButtonEvent : public Event
   {
      public:
         inline int GetMouseButton() const { return _button; }

         EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

      protected:
         MouseButtonEvent(int button) : _button(button) {}
         int _button;
   };

   class MouseButtonPressedEvent : public MouseButtonEvent
   {
      public:
         MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

         std::string toString() const override
         {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: [button: " << _button << "]" << std::endl;
            return ss.str();
         }

         EVENT_CLASS_TYPE(MouseButtonPressed)
   };
   class MouseButtonReleasedEvent : public MouseButtonEvent
   {
      public:
         MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

         std::string toString() const override
         {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: [button: " << _button << "]" << std::endl;
            return ss.str();
         }

         EVENT_CLASS_TYPE(MouseButtonReleased)
   };



}


#endif //CLAYENGINE_MOUSEEVENT_H
