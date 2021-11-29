//
// Created by quantum on 11/5/21.
//

#include "MeshTools.h"
#include "Platforms/OpenCL/OpenCL.h"

namespace Clay
{
   static OpenCL* s_OpenCL = new OpenCL(std::string(ASSETS_PATH) + "/Kernels/kernels.cpp");

   void MeshTools::LaunchKernel()
   {
      uint8_t bufferA = s_OpenCL->CreateBufferInt(60);
      uint8_t bufferB = s_OpenCL->CreateBufferInt(60);
      uint8_t bufferC = s_OpenCL->CreateBufferInt(60);

      s_OpenCL->SetArgument("surfaceKernel", 0, bufferA);
      s_OpenCL->SetArgument("surfaceKernel", 1, bufferB);
      s_OpenCL->SetArgument("surfaceKernel", 2, bufferC);

      s_OpenCL->commandQueue.enqueueNDRangeKernel(s_OpenCL->kernels["surfaceKernel"], cl::NullRange, cl::NDRange(60), cl::NullRange);

      int result[60];
      s_OpenCL->ReadBufferInt(bufferC, result, 60);

      for(int i = 0; i<60; i++)
      {
         printf("%d ", result[i]);
      }
      printf("\n");
   }

   void MeshTools::Circle(Ref<TriangleMesh>& model, uint16_t vertices)
   {
      float theta = 0;
      float angle = 360.0 / (float) vertices;
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertVertex(0, sin(theta / 180 * M_PI), cos(theta / 180 * M_PI));
         theta += angle;
      }
      uint32_t offset = 0;
      for(uint16_t i = 0; i< (vertices - 2) * 3; i+=3)
      {
         model->InsertIndex(0);
         model->InsertIndex(offset + 1);
         model->InsertIndex(offset + 2);
      }
   }

   void MeshTools::Cuboid(Ref<TriangleMesh>& model, float height, float width, float length)
   {
      // Generate Vertex Buffer for both top and bottom circles.

      model->InsertVertex(height/2, width/2, length/2);
      model->InsertVertex(height/2, -width/2, length/2);
      model->InsertVertex(-height/2, -width/2, length/2);
      model->InsertVertex(-height/2, width/2, length/2);

      model->InsertVertex(height/2, width/2, -length/2);
      model->InsertVertex(height/2, -width/2, -length/2);
      model->InsertVertex(-height/2, -width/2, -length/2);
      model->InsertVertex(-height/2, width/2, -length/2);

      // Set up Index Buffer for both top-bottom and side quads.
      uint16_t vertices = 4;
      int offset = 0;
      for(uint16_t i = 0; i< vertices - 2; i++)
      {
         model->InsertIndex(0);
         model->InsertIndex(offset + 1);
         model->InsertIndex(offset + 2);
         offset++;
      }
      offset = vertices;
      for(uint16_t i = 0; i< (vertices - 2) * 3; i+=3)
      {
         model->InsertIndex(vertices);
         model->InsertIndex(offset + 1);
         model->InsertIndex(offset + 2);
         offset++;
      }
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertIndex(i % vertices);
         model->InsertIndex(vertices + (i % vertices));
         model->InsertIndex(vertices + ((i+1) % (vertices)));
      }
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertIndex(i % vertices);
         model->InsertIndex(vertices + ((i+1) % (vertices)));
         model->InsertIndex((i+1) % vertices);
      }
   }

   void MeshTools::Sphere(Ref<TriangleMesh>& model, float radius, int sectors, int stacks, const SurfaceParameters& params)
   {
      // Generate Vertex Buffer for both top and bottom circles.
      float stackStep = M_PI / stacks;
      float sectorStep = 2 * M_PI / sectors;

      float stackAngle, sectorAngle, x, y, xy, z, u, v, h;

      for(uint16_t i = 0; i<=stacks; i++)
      {
         stackAngle = M_PI / 2 - i * stackStep;
         xy = radius * cosf(stackAngle);
         z = radius * sinf(stackAngle);

         for(uint16_t j = 0; j<=sectors; j++)
         {
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            u = ((M_PI / 2) - stackAngle) / M_PI;
            v = sectorAngle / (2 * M_PI);

            h = params.CalculateHeight(u * 80, v * 80) * 0.02f;

            model->InsertVertex(x*(1+h), y*(1+h), z*(1+h));
         }
      }

      // Set up Index Buffer for both top-bottom and side quads.
      uint16_t k1, k2;
      for(uint16_t i = 0; i < stacks; ++i)
      {
         k1 = i * (sectors + 1);     // beginning of current stack
         k2 = k1 + sectors + 1;      // beginning of next stack

         for(int j = 0; j < sectors; ++j, ++k1, ++k2)
         {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
               model->InsertIndex(k2);
               model->InsertIndex(k1);
               model->InsertIndex(k1 + 1);
            }
            // k1+1 => k2 => k2+1
            if(i != (stacks-1))
            {
               model->InsertIndex(k2);
               model->InsertIndex(k1 + 1);
               model->InsertIndex(k2 + 1);
            }
         }
      }
   }

   void MeshTools::Surface(Ref<TriangleMesh>& model, int uStepCount, int vStepCount)
   {
      float uStep = 1.0f / (float)uStepCount;
      float vStep = 1.0f / (float)vStepCount;
      float uPos, vPos;
      for(int u = 0; u<uStepCount; u++)
      {
         uPos = u * uStep - 0.5f;
         for(int v = 0; v<vStepCount; v++)
         {
            vPos = v * vStep - 0.5f;
            float zPos = 4 * pow(uPos, 3) + 3 * pow(vPos, 2);
            model->InsertVertex(uPos, zPos, vPos);
         }
      }

      for(int u = 0; u<uStepCount-1; u++)
      {
         for(int v = 0; v<vStepCount-1; v++)
         {
            model->InsertIndex(u * uStepCount + v);
            model->InsertIndex(((u+1) % uStepCount) * uStepCount + v);
            model->InsertIndex((u) * uStepCount + ((v+1) % vStepCount));

            model->InsertIndex((u) * uStepCount + ((v+1) % vStepCount));
            model->InsertIndex(((u+1) % uStepCount) * uStepCount + v);
            model->InsertIndex(((u+1) % uStepCount) * uStepCount + ((v+1) % vStepCount));
         }
      }
   }

    void MeshTools::Torus(Ref<TriangleMesh>& model, float innerRadius, float outerRadius, int innerCount, int outerCount)
    {
        // Generate Vertex Buffer for both top and bottom circles.
        float outerStep = 2 * M_PI / innerCount;
        float innerStep = 2 * M_PI / outerCount;

        float innerAngle, outerAngle, x, y, xy, z;

        for(uint16_t i = 0; i<=innerCount; i++)
        {
            innerAngle = M_PI / 2 - i * outerStep;
            xy = outerRadius * cosf(innerAngle);
            z = outerRadius * sinf(innerAngle * innerAngle);

            for(uint16_t j = 0; j<=outerCount; j++)
            {
                outerAngle = j * innerStep;
                x = xy * cosf(outerAngle);
                y = xy * sinf(outerAngle);
                model->InsertVertex(x, y, z);
            }
        }

        // Set up Index Buffer for both top-bottom and side quads.
        uint16_t k1, k2;
        for(uint16_t i = 0; i < innerCount; ++i)
        {
            k1 = i * (outerCount + 1);     // beginning of current stack
            k2 = k1 + outerCount + 1;      // beginning of next stack

            for(int j = 0; j < outerCount; ++j, ++k1, ++k2)
            {
                // 2 triangles per sector excluding first and last innerCount
                // k1 => k2 => k1+1
                if(i != 0)
                {
                    model->InsertIndex(k2);
                    model->InsertIndex(k1);
                    model->InsertIndex(k1 + 1);
                }
                // k1+1 => k2 => k2+1
                if(i != (innerCount-1))
                {
                    model->InsertIndex(k2);
                    model->InsertIndex(k1 + 1);
                    model->InsertIndex(k2 + 1);
                }
            }
        }
    }

    void MeshTools::LoadOBJ(Ref<TriangleMesh>& model, const std::string& filename)
    {
       std::ifstream objFile;
       objFile.open(filename);
       std::string line;

       bool startPoints = false;
       float x, y, z;

       while(std::getline(objFile, line))
       {
          std::istringstream iss(line);
          std::vector<std::string> words;
          boost::algorithm::split(words, line, boost::is_any_of(" "));

          if(words[0] == "v")
          {

             x = atof(words[1].c_str());
             y = atof(words[2].c_str());
             z = atof(words[3].c_str());

             model->InsertVertex(x,y,z);
          }

          if(words[0] == "f")
          {
             x = atoi(words[1].c_str());
             y = atoi(words[2].c_str());
             z = atoi(words[3].c_str());
             model->InsertIndex(y-1);
             model->InsertIndex(x-1);
             model->InsertIndex(z-1);
          }

       }
    }

   void MeshTools::LoadOFF(Ref<TriangleMesh>& model, const std::string& filename)
   {
      std::ifstream objFile;
      objFile.open(filename);
      std::string line;

      bool startPoints = false;
      float x, y, z;
      int a, b, c;

      int lineCount = 0;

      while(std::getline(objFile, line))
      {
         lineCount++;
         std::istringstream iss(line);
         std::vector<std::string> words;
         boost::algorithm::split(words, line, boost::is_any_of(" "));

         if(lineCount <= 2) continue;

         if(words.size() == 4 && words[0] != "3")
         {

            x = atof(words[0].c_str()) * 0.1;
            y = atof(words[1].c_str()) * 0.1;
            z = atof(words[2].c_str()) * 0.1;

            model->InsertVertex(x,y,z);

         }

         if(words[0] == "3")
         {
            a = atoi(words[1].c_str());
            b = atoi(words[2].c_str());
            c = atoi(words[3].c_str());
            model->InsertIndex(b);
            model->InsertIndex(a);
            model->InsertIndex(c);
         }

      }
   }

   void MeshTools::Cylinder(Ref<TriangleMesh>& model, uint16_t vertices, float radius, float height)
   {
      // Generate Vertex Buffer for both top and bottom circles.
      float theta = 0;
      float angle = 360.0 / (float) vertices;
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertVertex(height/2, radius * sin(theta / 180 * M_PI), radius * cos(theta / 180 * M_PI));
         theta += angle;
      }
      theta = 0;
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertVertex(-height/2, radius * sin(theta / 180 * M_PI), radius * cos(theta / 180 * M_PI));
         theta += angle;
      }

      // Set up Index Buffer for both circles and side quads.
      uint16_t totalTriangles = 4 * vertices - 4;
      int offset = 0;
      for(uint16_t i = 0; i< vertices - 2; i++)
      {
         model->InsertIndex(0);
         model->InsertIndex(offset + 1);
         model->InsertIndex(offset + 2);
         offset++;
      }
      offset = vertices;
      for(uint16_t i = 0; i< (vertices - 2) * 3; i+=3)
      {
         model->InsertIndex(vertices);
         model->InsertIndex(offset + 1);
         model->InsertIndex(offset + 2);
         offset++;
      }
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertIndex(i % vertices);
         model->InsertIndex(vertices + (i % vertices));
         model->InsertIndex(vertices + ((i+1) % (vertices)));
      }
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertIndex(i % vertices);
         model->InsertIndex(vertices + ((i+1) % (vertices)));
         model->InsertIndex((i+1) % vertices);
      }
      model->ResetIndexCount();
   }

   void MeshTools::CoordinateAxes(Ref<TriangleMesh>& model)
   {
      Ref<TriangleMesh> xModelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.2,0.8,0.2,1.0), nullptr);
      MeshTools::Cylinder(xModelMesh, 4, 0.01, 0.2f);
      xModelMesh->ApplyTransform({0, M_PI/2, 0}, {0.0, 0.0, 0.1});

      Ref<TriangleMesh> yModelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.8,0.2,0.2,1.0), nullptr);
      MeshTools::Cylinder(yModelMesh, 4, 0.01, 0.2f);
      yModelMesh->ApplyTransform({M_PI/2, 0, 0}, {0.1, 0.0, 0.0});

      Ref<TriangleMesh> zModelMesh = std::make_shared<TriangleMesh>(glm::vec4(0.2,0.2,0.8,1.0), nullptr);
      MeshTools::Cylinder(zModelMesh, 4, 0.01, 0.2f);
      zModelMesh->ApplyTransform({0, 0, M_PI/2}, {0.0, 0.1, 0.0});

      model->AddMesh(xModelMesh);
      model->AddMesh(yModelMesh);
      model->AddMesh(zModelMesh);

      CLAY_LOG_INFO("IndexCount: {}, VertexCount: {}, Indices: {}", model->GetPreviousIndexCount(), model->GetSize(), model->GetMesh()->_vertices.size());
   }
}
