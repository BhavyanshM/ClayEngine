#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace Clay
{
   OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : _path(path)
   {
      int width, height, channels;
      stbi_set_flip_vertically_on_load(1);
      stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

      if(!data)
         CLAY_LOG_INFO("Could Not Load Texture!");

      _width = width;
      _height = height;

      glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId);
      glTextureStorage2D(_rendererId, 1, GL_RGB8, _width, _height );

      glTextureParameteri(_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glTextureSubImage2D(_rendererId, 0,0,0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data);

      stbi_image_free(data);
   }

   OpenGLTexture2D::~OpenGLTexture2D()
   {
      glDeleteTextures(1, &_rendererId);
   }

   void OpenGLTexture2D::Bind(uint32_t slot) const
   {
      glBindTextureUnit(slot, _rendererId);
   }
}