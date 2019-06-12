#pragma once
#include <kraVertex.h>

#include "kraPrerequisitesCore.h"
#include "kraIndexBuffer.h"
#include "kraVertexBuffer.h"
#include "kraMaterial.h"

namespace kraEngineSDK {

  class Texture;

  class KRA_CORE_EXPORT Mesh
  {
  public:

    Mesh(Device& pDevice);
    Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices);
    Mesh(const Mesh& copyMesh);
    ~Mesh() {}

    void
    DrawMesh(Device* pDevice);
    
    Material&
    getMaterial();

    IndexBuffer*
    getIndexBuffer();

    VertexBuffer*
    getVertexBuffer();

    Vector<Texture*>& const
    getTextureVector();
    
  private:
    IndexBuffer* m_indexBuffer = nullptr;
    VertexBuffer* m_vertexBurffer = nullptr;
    Vector<Texture*> m_meshTextures;
    Material* m_material = nullptr;

  };
}
