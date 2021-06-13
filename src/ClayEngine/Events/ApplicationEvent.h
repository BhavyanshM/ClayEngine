//
// Created by quantum on 6/12/21.
//

#ifndef CLAYENGINE_APPLICATIONEVENT_H
#define CLAYENGINE_APPLICATIONEVENT_H

#include "Event.h"

namespace Clay

{
   class WindowResizeEvent : public Event
   {
      public:
         WindowResizeEvent(unsigned int width, unsigned int height) : _width(width), _height(height) {}

         inline int GetWidth() const {return _width;}
         inline int GetHeight() const {return _height;}

         std::string toString() const override
         {
            std::stringstream ss;
            ss << "WindowResizeEvent: [width: " << _width << ", height: " << _height << "]" << std::endl;
            return ss.str();
         }

         EVENT_CLASS_CATEGORY(EventCategoryApplication)
         EVENT_CLASS_TYPE(WindowResize)

      private:
         unsigned int _width, _height;
   };

   class WindowCloseEvent : public Event
   {
      public:
         WindowCloseEvent(){}

         EVENT_CLASS_TYPE(WindowClose)
         EVENT_CLASS_CATEGORY(EventCategoryApplication)
   };


   class AppTickEvent : public Event
   {
      public:
         AppTickEvent(){}

         EVENT_CLASS_TYPE(AppTick)
         EVENT_CLASS_CATEGORY(EventCategoryApplication)
   };


   class AppRenderEvent : public Event
   {
      public:
         AppRenderEvent(){}

         EVENT_CLASS_TYPE(AppRender)
         EVENT_CLASS_CATEGORY(EventCategoryApplication)
   };


   class AppUpdateEvent : public Event
   {
      public:
         AppUpdateEvent(){}

         EVENT_CLASS_TYPE(AppUpdate)
         EVENT_CLASS_CATEGORY(EventCategoryApplication)
   };

}

#endif //CLAYENGINE_APPLICATIONEVENT_H
