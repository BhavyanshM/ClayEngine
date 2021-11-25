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

   void MeshTools::Sphere(Ref<TriangleMesh>& model, float radius, int sectors, int stacks)
   {
      // Generate Vertex Buffer for both top and bottom circles.
      float stackStep = M_PI / stacks;
      float sectorStep = 2 * M_PI / sectors;

      float stackAngle, sectorAngle, x, y, xy, z;

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
            model->InsertVertex(x, y, z);
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
}
