//
// Created by quantum on 6/23/21.
//

#ifndef CLAYENGINE_TEXTURE_H
#define CLAYENGINE_TEXTURE_H

#include "Core/Core.h"

namespace Clay
{
   class Texture
   {
      public:
         virtual ~Texture() = default;

         virtual uint32_t GetWidth() const = 0;
         virtual uint32_t GetHeight() const = 0;
         virtual uint32_t GetRendererId() const = 0;

         virtual void Bind(uint32_t slot = 0) const = 0;
   };

   class Texture2D : public Texture
   {
      public:

         static Ref<Texture2D> Create(const std::string& path);

   };

}

#endif //CLAYENGINE_TEXTURE_H
