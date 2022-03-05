//
// Created by quantum on 9/24/21.
//


#include "PointCloud.h"

namespace Clay
{
   PointCloud::PointCloud(const glm::vec4& color, const Ref<Model>& parent) : Model(parent, true, 400000)
   {
      _mesh->_color = color;
      _mesh->_type = RendererAPI::MODE::Points;
   }

   void PointCloud::InsertVertex(float x, float y, float z)
   {
      if (_mesh->_index < _mesh->MAX_POINTS - 10)
      {
         _mesh->_vertices.emplace_back(x);
         _mesh->_vertices.emplace_back(y);
         _mesh->_vertices.emplace_back(z);
         _mesh->_index++;
      }
   }

   void PointCloud::InsertIndex(uint32_t index)
   {
      if (index < _mesh->MAX_POINTS - 10)
      {
         _mesh->_indices.emplace_back(index);
      }
   }

   void PointCloud::Reset()
   {
      _mesh->_vertices.clear();
      _mesh->_indices.clear();
      _mesh->_index = 0;
   }

   void PointCloud::Load(const std::string& filename, bool applyTransformToWorld)
   {
      CLAY_LOG_INFO("Loading PointCloud from: {}", filename);

      /* Read and Fill.*/
      std::ifstream pcdFile;
      //      std::string filePath = std::string(ASSETS_PATH) + "Meshes/bunny.pcd";
      std::string filePath = filename;
      pcdFile.open(filePath);
      std::string line;
      bool startPoints = false;
      float x, y, z;

      CLAY_LOG_INFO("Reading Points Now.");
      while (std::getline(pcdFile, line))
      {
         std::istringstream iss(line);
         if (line == "DATA ascii")
         {
            startPoints = true;
         } else if (startPoints)
         {
            std::vector<std::string> words;
            boost::algorithm::split(words, line, boost::is_any_of(" "));

            if(applyTransformToWorld)
            {
                z = -atof(words[0].c_str());
                x = -atof(words[1].c_str());
                y = atof(words[2].c_str());
            }
            else
            {
                x = atof(words[0].c_str());
                y = atof(words[1].c_str());
                z = atof(words[2].c_str());
            }
            if (x * x + y * y + z * z > 0.001)
            {
               InsertVertex(x, y, z);
            }
         }
      }
      pcdFile.close();

      CLAY_LOG_INFO("PointCloud Created with {} points.!", GetSize());
   }

   void PointCloud::LoadOFFVertices(const std::string& filename)
   {
      std::ifstream objFile;
      objFile.open(filename);
      std::string line;

      bool startPoints = false;
      float x, y, z;
      int a, b, c;

      int lineCount = 0;

      while (std::getline(objFile, line))
      {
         lineCount++;
         std::istringstream iss(line);
         std::vector<std::string> words;
         boost::algorithm::split(words, line, boost::is_any_of(" "));

         if (lineCount <= 2)
            continue;

         if (words.size() == 4 && words[0] != "3" && lineCount % 5 == 0)
         {

            x = atof(words[0].c_str()) ;
            y = atof(words[1].c_str()) ;
            z = atof(words[2].c_str()) ;

            InsertVertex(x, y, z);
         }
      }
   }

   void PointCloud::Print()
   {
      for (int i = 0; i < GetSize(); i++)
      {
         CLAY_LOG_INFO("Point: {} {} {}", _mesh->_vertices[i * 3], _mesh->_vertices[i * 3 + 1], _mesh->_vertices[i * 3 + 2]);
      }
   }
}