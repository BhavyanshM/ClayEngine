//
// Created by quantum on 6/19/21.
//

#include "RenderCommand.h"
#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Clay
{
   RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}