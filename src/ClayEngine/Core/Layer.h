//
// Created by quantum on 6/14/21.
//

#ifndef CLAYENGINE_LAYER_H
#define CLAYENGINE_LAYER_H

#include "Core.h"
#include "Events/Event.h"

namespace Clay
{
   class Layer
   {
      public:
         Layer(const std::string& name = "Layer");

         virtual ~Layer();

         virtual void OnAttach() {};
         virtual void OnDetach() {};
         virtual void OnUpdate(Timestep ts) {};
         virtual void OnEvent(Event& e) {};
         virtual void OnImGuiRender() {};

         inline std::string GetName() const { return _debugName; }

      protected:
         std::string _debugName;
   };
}

#endif //CLAYENGINE_LAYER_H
