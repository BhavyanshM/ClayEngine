
#include "FileBrowserUI.h"
#include "imgui/imgui.h"

namespace Clay
{
   static std::filesystem::path currentDirectory = "/home/quantum/Workspace/Storage/Other/Temp/dataset/ModelNet40/";
   static const std::filesystem::path ASSETS_DIRECTORY = "/home/quantum/Workspace/Storage/Other/Temp/dataset/ModelNet40/";

   void FileBrowserUI::ImGuiUpdate()
   {
      if(currentDirectory != std::filesystem::path(ASSETS_DIRECTORY))
      if(ImGui::Button("<-"))
      {
         currentDirectory = currentDirectory.parent_path();
      }
      for(auto& dir : std::filesystem::directory_iterator(currentDirectory))
      {
         const auto& path = dir.path();
         auto relativePath = std::filesystem::relative(path, currentDirectory);
         if(ImGui::Button(path.filename().c_str()))
         {
            if(dir.is_directory())
               currentDirectory /= path.filename();
         }
      }
   }

   void FileBrowserUI::FileDialog()
   {
      
   }
}