//
// Created by quantum on 6/14/21.
//

#ifndef CLAYENGINE_LAYERSTACK_H
#define CLAYENGINE_LAYERSTACK_H

#include "Core.h"
#include "Layer.h"

namespace  Clay
{

   class LayerStack
   {
      public:
         LayerStack() = default;
         ~LayerStack();

         void PushLayer(Layer* layer);
         void PushOverlay(Layer* overlay);
         void PopLayer(Layer* layer);
         void PopOverlay(Layer* overlay);

         std::vector<Layer*>::iterator begin() { return _layers.begin();}
         std::vector<Layer*>::iterator end() { return _layers.end();}

      private:
         std::vector<Layer*> _layers;
         unsigned int _layerInsertIndex = 0;

   };

}
#endif //CLAYENGINE_LAYERSTACK_H
