//
// Created by quantum on 9/24/21.
//


#include "PointCloud.h"

namespace Clay
{
   PointCloud::PointCloud(const std::string& filename, const glm::vec4& color, const Ref<Model>& parent) : Model(parent, true, 400000)
   {
      CLAY_LOG_INFO("Creating PointCloud!");

      _mesh->_color = color;
      _mesh->_type = RendererAPI::MODE::Points;

      /* Read and Fill.*/
      std::ifstream pcdFile;
      std::string filePath = std::string(ASSETS_PATH) + "Meshes/bunny.pcd";
      pcdFile.open(filePath);
      std::string line;
      bool startPoints = false;
      float x, y, z;
      while (std::getline(pcdFile, line))
      {
         std::istringstream iss(line);
         if (line == "DATA ascii")
         {
            startPoints = true;
         }
         else if (startPoints)
         {
            std::vector<std::string> words;
            boost::algorithm::split(words, line, boost::is_any_of(" "));

            x = atof(words[0].c_str());
            y = atof(words[1].c_str());
            z = atof(words[2].c_str());
            Insert(x,y,z);
         }
      }
      pcdFile.close();

      Upload();
   }

   PointCloud::PointCloud(const glm::vec4& color, const Ref<Model>& parent) : Model(parent, true, 400000)
   {
      _mesh->_color = color;
      _mesh->_type = RendererAPI::MODE::Points;
   }

   void PointCloud::Insert(float x, float y, float z)
   {
      if(_mesh->_index < _mesh->MAX_POINTS - 10)
      {
         _mesh->_indices.emplace_back(_mesh->_index);
         _mesh->_vertices.emplace_back(x);
         _mesh->_vertices.emplace_back(y);
         _mesh->_vertices.emplace_back(z);
         _mesh->_index++;
      }
   }

   void PointCloud::Upload()
   {
      /* Setup for Vertex Array */
      BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}};
      _mesh->_vertexArray = VertexArray::Create();
      _mesh->_vertexBuffer = VertexBuffer::Create(_mesh->_vertices.data(), _mesh->_index);
      _mesh->_indexBuffer = IndexBuffer::Create(_mesh->_indices.data(), _mesh->_index);
      _mesh->_vertexBuffer->SetLayout(layout);
      _mesh->_vertexArray->AddVertexBuffer(_mesh->_vertexBuffer);
      _mesh->_vertexArray->SetIndexBuffer(_mesh->_indexBuffer);
   }

   void PointCloud::Reset()
   {
      _mesh->_vertices.clear();
      _mesh->_indices.clear();
      _mesh->_index = 0;
   }


}