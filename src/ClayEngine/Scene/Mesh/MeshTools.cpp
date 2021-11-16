//
// Created by quantum on 11/5/21.
//

#include "MeshTools.h"


namespace Clay
{
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

   void MeshTools::Cylinder(Ref<TriangleMesh>& model, uint16_t vertices, float height)
   {
      // Generate Vertex Buffer for both top and bottom circles.
      float theta = 0;
      float angle = 360.0 / (float) vertices;
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertVertex(height/2, sin(theta / 180 * M_PI), cos(theta / 180 * M_PI));
         theta += angle;
      }
      theta = 0;
      for(uint16_t i = 0; i<vertices; i++)
      {
         model->InsertVertex(-height/2, sin(theta / 180 * M_PI), cos(theta / 180 * M_PI));
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

}


/*
 * 0 - 1 - 2 - 3
 * 4 - 5 - 6 - 7
 * 8 - 9 - 10 - 11
 * 12 - 13 - 14 - 15
 *
 * 0 - 4 - 1
 * 1 - 5 - 2
 * 2 - 6 - 3
 *
 * */