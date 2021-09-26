//
// Created by quantum on 9/24/21.
//


#include "PointCloud.h"


namespace Clay
{
   std::vector<std::string> split(const std::string& input, const std::string& regex) {
      // passing -1 as the submatch index parameter performs splitting
      std::regex re(regex);
      std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
      return {first, last};
   }

   PointCloud::PointCloud(const std::string& filename)
   {
      CLAY_LOG_INFO("Creating PointCloud!");

      uint32_t indices[397];
      float vertices[397 * 3];

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
//            std::cout << line << std::endl;

            std::vector<std::string> words;
            boost::algorithm::split(words, line, boost::is_any_of(" "));

            x = atof(words[0].c_str());
            y = atof(words[1].c_str());
            z = atof(words[2].c_str());

//            CLAY_LOG_INFO("Index: {} - Point: ({}, {}, {})", index, x, y, z);
            indices[_index] = _index;
            vertices[_index*3 + 0] = x;
            vertices[_index*3 + 1] = y;
            vertices[_index*3 + 2] = z;
            _index++;
         }
      }
      pcdFile.close();

      /* Setup for Vertex Array */
      BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}};
      _vertexArray = VertexArray::Create();
      _vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
      _indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

      _vertexBuffer->SetLayout(layout);
      _vertexArray->AddVertexBuffer(_vertexBuffer);
      _vertexArray->SetIndexBuffer(_indexBuffer);

   }

}