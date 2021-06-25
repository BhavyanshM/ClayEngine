//
// Created by quantum on 6/24/21.
//

#ifndef CLAYENGINE_FRAMEBUFFER_H
#define CLAYENGINE_FRAMEBUFFER_H

#include "Core/Core.h"

namespace Clay
{

   struct FramebufferSpecification
   {
      uint32_t height, width;
      uint32_t samples = 1;
      bool SwapChainTarget = false;
   };

   class FrameBuffer
   {
      public:
         virtual const FramebufferSpecification& GetSpecification() = 0;

         virtual uint32_t GetColorAttachment() const = 0;

         virtual void Bind() const = 0;
         virtual void Unbind() const = 0;

         static Ref<FrameBuffer> Create(const FramebufferSpecification& spec);
   };
}

#endif //CLAYENGINE_FRAMEBUFFER_H
