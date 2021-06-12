//
// Created by quantum on 6/12/21.
//

#ifndef CLAYENGINE_EVENT_H
#define CLAYENGINE_EVENT_H

namespace Clay
{
   enum class EventType
   {
         None = 0,
         WindowClose,
         WindowResize,
         WindowClose,
         WindowLostFocus,
         WindowMoved,
         AppTick,
         AppRender,
         AppUpdate,
         KeyPressed,
         KeyReleased,
         MouseButtonPressed,
         MouseButtonReleased,
         MouseMoved,
         MouseScrolled
   };

   enum EventCategory
   {
      None = 0,
      EventCategoryApplication = (1 << 0),
      EventCategoryInput = (1 << 1),
      EventCategoryKeyboard = (1 << 2),
      EventCategoryMouse = (1 << 3),
      EventCategoryMouseInput = (1 << 4),
   };

   class Event
   {
         friend class EventDispatcher;
      public:
         virtual EventType GetEventType() const = 0;
         virtual const char* GetName() const = 0;
         virtual int GetCategoryFlags() const = 0;
         virtual int std::string toString() const { return GetName(); };

         inline bool IsInCategory(EventCategory category)
         {
            return GetCategoryFlags() & category;
         }

      protected:
         bool _handled = false;
   };

   class EventDispatcher
   {

   };
}

#endif //CLAYENGINE_EVENT_H
