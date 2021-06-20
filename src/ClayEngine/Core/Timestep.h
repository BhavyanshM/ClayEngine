//
// Created by quantum on 6/20/21.
//

#ifndef CLAYENGINE_TIMESTEP_H
#define CLAYENGINE_TIMESTEP_H

namespace Clay
{
   class Timestep
   {
      public:

         Timestep(float time = 0.0f)
            : _duration(time)
         {
         }

         operator float() const {return _duration;}

         double GetSeconds() const {return _duration; };
         double GetMilliseconds() const {return _duration * 1000; };

      private:
         double _duration;
   };
}

#endif //CLAYENGINE_TIMESTEP_H
