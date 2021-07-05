#include "OpenGLTexture.h"
#include "stb_image.h"

namespace Clay
{
   OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
   {
      _width = width;
      _height = height;
      _internalFormat = GL_RGBA8;
      _dataFormat = GL_RGBA;

      glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId);
      glTextureStorage2D(_rendererId, 1, _internalFormat, _width, _height);

      glTextureParameteri(_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
   }

   OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : _path(path)
   {
      int width, height, channels;
      stbi_set_flip_vertically_on_load(1);
      stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

      if (!data)
         CLAY_LOG_INFO("Could Not Load Texture!");

      _width = width;
      _height = height;

      GLenum internalFormat = 0, dataFormat = 0;
      if (channels == 4)
      {
         internalFormat = GL_RGBA8;
         dataFormat = GL_RGBA;
      } else if (channels == 3)
      {
         internalFormat = GL_RGB8;
         dataFormat = GL_RGB;
      }

      _internalFormat = internalFormat;
      _dataFormat = dataFormat;

      glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId);
      glTextureStorage2D(_rendererId, 1, internalFormat, _width, _height);

      glTextureParameteri(_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glTextureSubImage2D(_rendererId, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data);

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

   void OpenGLTexture2D::SetData(void *data, uint32_t size)
   {
      uint32_t bpc = _dataFormat == GL_RGBA ? 4 : 3;
      glTextureSubImage2D(_rendererId, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
   }
}