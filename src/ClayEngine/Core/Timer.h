//
// Created by quantum on 7/4/21.
//

#ifndef CLAYENGINE_TIMER_H
#define CLAYENGINE_TIMER_H

#include "ClayHeaders.h"

namespace Clay
{
   template<typename Fn>
   class Timer
   {
      public:

         Timer(const char* name, Fn&& func) : _name(name), _stopped(false), _func(func)
         {
            _startPoint = std::chrono::steady_clock::now();
         }

         ~Timer()
         {
            auto end_point = std::chrono::steady_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_startPoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_point).time_since_epoch().count();

            float duration = (end - start) * 0.001f;

            _stopped = true;

            _func({_name, duration});
         }

      private:
         const char* _name;
         std::chrono::time_point<std::chrono::steady_clock> _startPoint;
         bool _stopped = false;
         Fn _func;
   };
}

#define PROFILE_SCOPE(name) Clay::Timer timer##_LINE__(name, [&](ProfileResult profileResult){_profileResults.push_back(profileResult);})


#endif //CLAYENGINE_TIMER_H
