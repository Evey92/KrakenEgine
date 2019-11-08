#pragma once
#include <kraVertex.h>

#include "kraPrerequisitesCore.h"
#include "kraIndexBuffer.h"
#include "kraVertexBuffer.h"
#include "kraMaterial.h"

namespace kraEngineSDK {

  class Texture;

  class KRA_CORE_EXPORT Mesh :
  public Component {
  
    CLASS_DECLARATION(Mesh)

   public:

     Mesh(Device& pDevice, GameObject* owner);

    ~Mesh() {}

    void
    initialize(Device& pDevice);

    void 
    initBuffers(std::vector<Vertex> vertices, 
               std::vector<uint32> indices);

    void
    DrawMesh(Device* pDevice);
    
    IndexBuffer*
    getIndexBuffer();

    VertexBuffer*
    getVertexBuffer();

    Vector<ShrdPtr<Texture>>& const
    getTextures();

    void
    setTexture(Device* pDevice, TEXTURE_TYPE::E texType, ShrdPtr<Texture> newTex);

    void
    setMeshMaterial(Device* pDevice, Material* mat);

    ShrdPtr<Texture>
    getTexture(TEXTURE_TYPE::E texType);

    
  private:
    Material m_material = nullptr;
    IndexBuffer* m_indexBuffer = nullptr;
    VertexBuffer* m_vertexBurffer = nullptr;
    Vector<ShrdPtr<Texture>> m_meshTextures;

  };
}
