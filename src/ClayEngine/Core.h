//
// Created by quantum on 6/12/21.
//

#ifndef CLAYENGINE_CORE_H
#define CLAYENGINE_CORE_H

#include "Log.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "Core/Timestep.h"

#include "memory"

namespace Clay
{
   template<typename T>
   using Ref = std::shared_ptr<T>;

   template<typename T>
   using Scope = std::unique_ptr<T>;
}

#endif //CLAYENGINE_CORE_H
