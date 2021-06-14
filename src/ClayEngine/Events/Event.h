//
// Created by quantum on 6/12/21.
//

#ifndef CLAYENGINE_EVENT_H
#define CLAYENGINE_EVENT_H

#include <sstream>


namespace Clay
{
   enum class EventType
   {
         None = 0,
         WindowClose,
         WindowResize,
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

#define EVENT_CLASS_TYPE(type)   static EventType GetStaticType() { return EventType::type; } \
                                 virtual EventType GetEventType() const override  { return GetStaticType(); } \
                                 virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


   class Event
   {
         friend class EventDispatcher;
      public:
         virtual EventType GetEventType() const = 0;
         virtual const char* GetName() const = 0;
         virtual int GetCategoryFlags() const = 0;
         virtual std::string toString() const { return GetName(); };

         inline bool IsInCategory(EventCategory category)  { return GetCategoryFlags() & category;}
         inline bool IsHandled() const { return _handled; }
         inline void SetHandled() { _handled = true; }

      protected:
         bool _handled = false;
   };

   class EventDispatcher
   {
         template<typename T>
         using EventFn = std::function<bool(T&)>;

      public:
         EventDispatcher(Event& event) : _event(event) {}

         template<typename T>
         bool Dispatch(EventFn<T> func)
         {
            if(_event.GetEventType() == T::GetStaticType())
            {
               _event._handled = func(*(T*)&_event);
               return true;
            }
            return false;
         }

      private:
         Event& _event;
   };

   inline std::ostream& operator<<(std::ostream& os, const Event& e)
   {
      return os << e.toString();
   }
}

#endif //CLAYENGINE_EVENT_H
