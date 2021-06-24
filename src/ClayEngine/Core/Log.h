//
// Created by quantum on 6/11/21.
//

#ifndef CLAYENGINE_LOG_H
#define CLAYENGINE_LOG_H

#include "ClayHeaders.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>

#define CLAY_LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define CLAY_LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define CLAY_LOG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define CLAY_LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define CLAY_LOG_FATAL(...) spdlog::fatal(__VA_ARGS__)

namespace Clay{
   class Log
   {
      public:
         static void Init();
   };
}



#endif //CLAYENGINE_LOG_H
