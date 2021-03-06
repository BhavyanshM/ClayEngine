//
// Created by quantum on 6/23/21.
//

#ifndef CLAYENGINE_OPENGLTEXTURE_H
#define CLAYENGINE_OPENGLTEXTURE_H

#include "Renderer/Texture.h"
#include "glad/glad.h"

namespace Clay
{

   class OpenGLTexture2D : public Texture2D
   {
      public:
         OpenGLTexture2D() = default;
         OpenGLTexture2D(const std::string& path);
         OpenGLTexture2D(uint32_t width, uint32_t height);
         virtual ~OpenGLTexture2D();

         uint32_t GetWidth() const override  {return _width;}
         uint32_t GetHeight() const override {return _height;}
         void LoadTexture(unsigned char* data, int width, int height, int channels) override;
         void LoadImage(unsigned char* data, int width, int height, int channels) override;
         virtual uint32_t GetRendererId() const override {return _rendererId;};
         void SetData(void* data, uint32_t size) override;

         void Bind(uint32_t slot = 0) const override;

         virtual bool operator==(const Texture& other) const override
         {
            return _rendererId == ((OpenGLTexture2D&) other)._rendererId;
         };



      private:
         std::string _path;
         uint32_t _height;
         uint32_t _width;
         uint32_t _rendererId;

         GLenum _internalFormat, _dataFormat;

   };

}

#endif //CLAYENGINE_OPENGLTEXTURE_H
