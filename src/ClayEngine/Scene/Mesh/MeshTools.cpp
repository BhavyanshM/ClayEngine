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
}