//
// Created by quantum on 9/24/21.
//


#include "TriangleMesh.h"

namespace Clay
{
   TriangleMesh::TriangleMesh(const glm::vec4& color, const Ref<Model>& parent) : Model(parent, true, 400000)
   {
      _mesh->_color = color;
      _mesh->_type = RendererAPI::MODE::Triangles;
   }

   void TriangleMesh::InsertVertex(float x, float y, float z)
   {
      if(_mesh->_index < _mesh->MAX_POINTS - 10)
      {
//         CLAY_LOG_INFO("Inserting: {} {} {}", x, y, z);
         _mesh->_vertices.emplace_back(x);
         _mesh->_vertices.emplace_back(y);
         _mesh->_vertices.emplace_back(z);
         _mesh->_index++;
      }
   }

   void TriangleMesh::InsertIndex(uint32_t index)
   {
      if(index < _mesh->MAX_POINTS - 10)
      {
         _mesh->_indices.emplace_back(index + _mesh->_cummulativeIndexCount);
      }
   }

   void TriangleMesh::Reset()
   {
      _mesh->_vertices.clear();
      _mesh->_indices.clear();
      _mesh->_index = 0;
   }

   void TriangleMesh::Print()
   {
      for(int i = 0; i<GetSize(); i++)
      {
         CLAY_LOG_INFO("Point: {} {} {}", _mesh->_vertices[i*3], _mesh->_vertices[i*3+1], _mesh->_vertices[i*3+2]);
      }
   }


}