//
// Created by quantum on 6/11/21.
//

#ifndef CLAYENGINE_LOG_H
#define CLAYENGINE_LOG_H

#include "ClayHeaders.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>

#if LOG_DEBUG == 1
#define CLAY_LOG_DEBUG(...) SPDLOG_INFO(__VA_ARGS__)
#elif LOG_DEBUG == 0
#define CLAY_LOG_DEBUG(...)
#endif


#define CLAY_LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define CLAY_LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define CLAY_LOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define CLAY_LOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define CLAY_LOG_FATAL(...) SPDLOG_FATAL(__VA_ARGS__)

namespace Clay{
   class Log
   {
      public:
         static void Init();
   };
}



#endif //CLAYENGINE_LOG_H
