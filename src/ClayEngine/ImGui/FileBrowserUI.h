
#ifndef CLAYENGINE_FILEBROWSERUI_H
#define CLAYENGINE_FILEBROWSERUI_H

#include "filesystem"

namespace Clay
{
   class FileBrowserUI
   {
      public:
         static void ImGuiUpdate();
         static void FileDialog();
   };
}

#endif //CLAYENGINE_FILEBROWSERUI_H
