//
// Created by quantum on 9/24/21.
//


#include <ext/matrix_transform.hpp>
#include "PointCloud.h"


namespace Clay
{
   PointCloud::PointCloud(const std::string& filename, const glm::vec4& color) : _color(color), _transform(1.0f)
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

   void PointCloud::RotateLocal(float angle, const glm::vec3& axis, bool radians)
   {
      _transform = glm::rotate(glm::mat4(1.0f), angle, axis) * _transform;
   }

   void PointCloud::RotateLocalX(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(1.0f,0.0f,0.0f), radians);
   }

   void PointCloud::RotateLocalY(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(0,1,0), radians);
   }

   void PointCloud::RotateLocalZ(float angle, bool radians)
   {
      RotateLocal(angle, glm::vec3(0,0,1), radians);
   }

   void PointCloud::TranslateLocal(const glm::vec3& translation)
   {
      //      _transform = glm::transpose(glm::translate(glm::mat4(1.0f), translation)) * _transform;

      _transform[3][0] += translation[0];
      _transform[3][1] += translation[1];
      _transform[3][2] += translation[2];
   }

}