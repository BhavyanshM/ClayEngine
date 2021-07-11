//
// Created by quantum on 6/24/21.
//

#ifndef CLAYENGINE_OPENGLFRAMEBUFFER_H
#define CLAYENGINE_OPENGLFRAMEBUFFER_H

#include "Renderer/FrameBuffer.h"

namespace Clay
{
   class OpenGLFrameBuffer : public FrameBuffer
   {
      public:
         OpenGLFrameBuffer(const FramebufferSpecification& spec);
         virtual ~OpenGLFrameBuffer();

         virtual void Bind() const override;
         virtual void Unbind() const override;

         virtual uint32_t GetColorAttachment() const override {return _colorAttachment;};

         virtual const FramebufferSpecification& GetSpecification() override {return _fbSpec;};

         virtual void Resize(uint32_t width, uint32_t height) override;

         void Invalidate();

      private:
         uint32_t _rendererId;
         uint32_t _colorAttachment;
         uint32_t _depthAttachment;
         FramebufferSpecification _fbSpec;

   };

}

#endif //CLAYENGINE_OPENGLFRAMEBUFFER_H
