#include "OpenGLTexture.h"
#include "stb_image.h"

namespace Clay
{
   OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
   {
      CLAY_PROFILE_FUNCTION();
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
      CLAY_PROFILE_FUNCTION();
      int width, height, channels;
      stbi_set_flip_vertically_on_load(1);
      stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

      // Generate a number for our _rendererId's unique handle
      glGenTextures(1, &_rendererId);
      LoadTexture(data, width, height, channels);

   }

   void OpenGLTexture2D::LoadTexture(unsigned char* data, int width, int height, int channels)
   {
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

   void OpenGLTexture2D::LoadImage(unsigned char* data, int width, int height, int channels)
   {
      if (!data)
         CLAY_LOG_INFO("Could Not Load Texture!");

//      _width = width;
//      _height = height;
//
//      GLenum internalFormat = 0, dataFormat = 0;
//      if (channels == 4)
//      {
//         internalFormat = GL_RGBA8;
//         dataFormat = GL_RGBA;
//      } else if (channels == 3)
//      {
//         internalFormat = GL_RGB8;
//         dataFormat = GL_RGB;
//      }
//
//      _internalFormat = internalFormat;
//      _dataFormat = dataFormat;
//
//      glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId);
//      glTextureStorage2D(_rendererId, 1, internalFormat, _width, _height);
//
//      glTextureParameteri(_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//      glTextureParameteri(_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//      glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
//      glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//      glTextureSubImage2D(_rendererId, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data);
//
//      stbi_image_free(data);

//      +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      // Bind to our texture handle
      glBindTexture(GL_TEXTURE_2D, _rendererId);

      // Set texture interpolation methods for minification and magnification
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      // Set texture clamping method
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      GLenum inputColourFormat = GL_BGR;

      // Create the texture
      glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                   0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                   GL_RGB,            // Internal colour format to convert to
                   width,          // Image width  i.e. 640 for Kinect in standard mode
                   height,          // Image height i.e. 480 for Kinect in standard mode
                   0,                 // Border width in pixels (can either be 1 or 0)
                   inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                   GL_UNSIGNED_BYTE,  // Image data type
                   data);        // The actual image data itself

   }

   OpenGLTexture2D::~OpenGLTexture2D()
   {
      CLAY_PROFILE_FUNCTION();
      glDeleteTextures(1, &_rendererId);
   }

   void OpenGLTexture2D::Bind(uint32_t slot) const
   {
      CLAY_PROFILE_FUNCTION();
      glBindTextureUnit(slot, _rendererId);
   }

   void OpenGLTexture2D::SetData(void *data, uint32_t size)
   {
      CLAY_PROFILE_FUNCTION();
      uint32_t bpc = _dataFormat == GL_RGBA ? 4 : 3;
      glTextureSubImage2D(_rendererId, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
   }
}