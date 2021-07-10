//
// Created by quantum on 6/24/21.
//

#include "OpenGLFrameBuffer.h"
#include "glad/glad.h"

namespace Clay
{
   OpenGLFrameBuffer::OpenGLFrameBuffer(const FramebufferSpecification& spec) : _fbSpec(spec)
   {
      Invalidate();
   }

   OpenGLFrameBuffer::~OpenGLFrameBuffer()
   {
      glDeleteFramebuffers(1, &_rendererId);
   }

   void OpenGLFrameBuffer::Invalidate()
   {
      glCreateFramebuffers(1, &_rendererId);
      glBindFramebuffer(GL_FRAMEBUFFER, _rendererId);

      glCreateTextures(GL_TEXTURE_2D, 1, &_colorAttachment);
      glBindTexture(GL_TEXTURE_2D, _colorAttachment);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _fbSpec.width, _fbSpec.height,0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);

      glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachment);
      glBindTexture(GL_TEXTURE_2D, _depthAttachment);
      glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _fbSpec.width, _fbSpec.height);

      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthAttachment, 0);

      if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
         CLAY_LOG_INFO("FrameBuffer Complete!");

      glBindFramebuffer(GL_FRAMEBUFFER, 0);

   }

   void OpenGLFrameBuffer::Bind() const
   {
      glBindFramebuffer(GL_FRAMEBUFFER, _rendererId);
   }

   void OpenGLFrameBuffer::Unbind() const
   {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
   }
}