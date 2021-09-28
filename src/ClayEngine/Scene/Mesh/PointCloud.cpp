//
// Created by quantum on 9/24/21.
//


#include "PointCloud.h"

namespace Clay
{
   PointCloud::PointCloud(const std::string& filename, const glm::vec4& color)
   {
      CLAY_LOG_INFO("Creating PointCloud!");

      _type = RendererAPI::MODE::Points;

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

   void PointCloud::Insert(float x, float y, float z)
   {
      if(_index < MAX_POINTS - 10)
      {
         _indices[_index] = _index;
         _vertices[_index * 3 + 0] = x;
         _vertices[_index * 3 + 1] = y;
         _vertices[_index * 3 + 2] = z;
         _index++;
      }
   }

   void PointCloud::Upload()
   {
      /* Setup for Vertex Array */
      BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}};
      _vertexArray = VertexArray::Create();
      _vertexBuffer = VertexBuffer::Create(_vertices, sizeof(_vertices));
      _indexBuffer = IndexBuffer::Create(_indices, sizeof(_indices) / sizeof(uint32_t));

      _vertexBuffer->SetLayout(layout);
      _vertexArray->AddVertexBuffer(_vertexBuffer);
      _vertexArray->SetIndexBuffer(_indexBuffer);
   }

   void PointCloud::Reset()
   {
      _index = 0;
   }


}