
#include "FileBrowserUI.h"
#include "imgui/imgui.h"


namespace Clay
{
   extern const std::filesystem::path ASSETS_DIRECTORY = ASSETS_PATH;

   FileBrowserUI::FileBrowserUI(const std::string& current)
   {
      currentDirectory = current;
      _directoryIcon = Texture2D::Create(std::string(ASSETS_PATH) + std::string("Textures/directory.png"));
      _fileIcon = Texture2D::Create(std::string(ASSETS_PATH) + std::string("Textures/file.png"));
   }

   bool FileBrowserUI::ImGuiUpdate(std::string& filePath)
   {
      ImGui::Begin("File Browser");

      bool final = true;

      static char searchCharBuffer[128];
      ImGui::InputText("Search: ", searchCharBuffer, IM_ARRAYSIZE(searchCharBuffer));
      searchString = std::string(searchCharBuffer);

      if(currentDirectory != ASSETS_DIRECTORY)
      {
         if(ImGui::Button("<-"))
         {
            filePath = currentDirectory;
            currentDirectory = currentDirectory.parent_path();
         }
      }
      ImGui::SameLine(50.0f);
      if(ImGui::Button("Open"))
      {
         filePath = currentDirectory;
         final = false;
      }

      static float padding = 16.0f;
      static float thumbnailSize = 128.0f;
      float cellSize = thumbnailSize + padding;

      float panelWidth = ImGui::GetContentRegionAvail().x;
      int columnCount = (int)(panelWidth / cellSize);
      if(columnCount < 1)
         columnCount = 1;

      ImGui::Columns(columnCount, 0, false);

      for(auto& dir : std::filesystem::directory_iterator(currentDirectory))
      {
         const auto& path = dir.path();
         auto relativePath = std::filesystem::relative(path, currentDirectory);
         std::string fileNameString = relativePath.filename().string();

         auto res = std::mismatch(searchString.begin(), searchString.end(), fileNameString.begin(), fileNameString.end());

         if(searchString.empty() || res.first == searchString.end())
         {
            Ref<Texture2D> icon = is_directory(dir) ? _directoryIcon : _fileIcon;
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
            ImGui::ImageButton((ImTextureID) icon->GetRendererId(), {thumbnailSize, thumbnailSize}, {0,1}, {1,0});
            ImGui::PopStyleColor();

            if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
               filePath = (currentDirectory / path.filename()).string();
               if(dir.is_directory())
               {
                  currentDirectory /= path.filename();
               }
               else
               {
                  final = false;
               }
            }
            ImGui::TextWrapped(fileNameString.c_str());

            ImGui::NextColumn();
         }


      }

      ImGui::Columns(1);
      ImGui::End();

      return final;
   }

   void FileBrowserUI::FileDialog()
   {
      
   }
}