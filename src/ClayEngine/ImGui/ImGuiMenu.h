//
// Created by shadylady on 11/22/21.
//

#ifndef CLAYENGINE_IMGUIMENU_H
#define CLAYENGINE_IMGUIMENU_H

#include "Renderer/Renderer.h"

namespace Clay
{
    class ImGuiMenu
    {
    public:
        static void MeshPrimitiveOptions(std::vector<Ref<Model>>& _models);
        static void RendererOptions();
        static void FileBrowser();
    };
}

#endif //CLAYENGINE_IMGUIMENU_H
