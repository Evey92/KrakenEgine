#pragma once
#include "kraPrerequisitesCore.h"
#include "kraIndexBuffer.h"
#include "kraVertexBuffer.h"
#include <kraVertex.h>

namespace kraEngineSDK {

  class KRA_CORE_EXPORT Mesh
  {
   public:
    
     Mesh() = default;
     Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices);
     Mesh(const Mesh& copyMesh);
    ~Mesh() {}


    IndexBuffer* m_indexBuffer;
    VertexBuffer* m_vertexBurffer;
    Vector<Vertex> m_vertices;
    Vector<uint32> m_indices;
  };
}
