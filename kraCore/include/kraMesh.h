#pragma once
#include <kraVertex.h>

#include "kraPrerequisitesCore.h"
#include "kraIndexBuffer.h"
#include "kraVertexBuffer.h"
#include "kraMaterial.h"

namespace kraEngineSDK {

  class KRA_CORE_EXPORT Mesh
  {
   public:
    
     Mesh(Device& pDevice);
     Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices);
     Mesh(const Mesh& copyMesh);
     ~Mesh() {}

    void
    DrawMesh(Device* pDevice);


    IndexBuffer* m_indexBuffer = nullptr;
    VertexBuffer* m_vertexBurffer = nullptr;
    Material* m_material = nullptr;
    
  };
}
