//
// Created by quantum on 6/11/21.
//


#include "Log.h"

namespace Clay
{
   void Log::Init()
   {
      spdlog::set_pattern("%^[%T] %n: %v%$");
   }

}