
#ifndef CLAYENGINE_FILEBROWSERUI_H
#define CLAYENGINE_FILEBROWSERUI_H

#include "filesystem"
#include "Renderer/Texture.h"

namespace Clay
{
   class FileBrowserUI
   {
      public:
         FileBrowserUI(const std::string& current);
         bool ImGuiUpdate(std::string& filePath);
         void FileDialog();

         void SetCurrentDirectory(const std::string& current);

      private:
         std::filesystem::path currentDirectory;
         std::string searchString;

         Ref<Texture2D> _directoryIcon;
         Ref<Texture2D> _fileIcon;
   };
}

#endif //CLAYENGINE_FILEBROWSERUI_H
