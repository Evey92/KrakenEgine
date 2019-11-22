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

     Mesh(Device& pDevice, const ShrdPtr<GameObject>& owner);

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

    const Vector<ShrdPtr<Texture>>&
    getTextures();

    void
    setTexture(Device* pDevice, TEXTURE_TYPE::E texType, const ShrdPtr<Texture>& newTex);

    void
    setMeshMaterial(Device* pDevice, Material* mat);

    void
    setMaterialAlbedo(Device* pDevice, const ShrdPtr<Texture>& newTex);

    void
    setMaterialNormal(ShrdPtr<Texture>& newTex);

    void
    setMaterialMetallic(ShrdPtr<Texture>& newTex);

    void
    setMaterialRoughness(ShrdPtr<Texture>& newTex);

    void
    setMaterialEmissive(ShrdPtr<Texture>& newTex);

    ShrdPtr<Texture>
    getTexture(TEXTURE_TYPE::E texType);

    void
    setName(String name);
    
    String
    getName();
  
    uint64
    getTotalIndex() { return m_totalIndex; }

    void
    setTotalIndex(uint64 indexes) { m_totalIndex = indexes; }

    uint64
    getTotalVert() { return m_totalVert; }

    void
    setTotalVert(uint64 vertex) { m_totalVert = vertex; }

   private:
    ShrdPtr<Material> m_material = nullptr;
    IndexBuffer* m_indexBuffer = nullptr;
    VertexBuffer* m_vertexBurffer = nullptr;
    Vector<ShrdPtr<Texture>> m_meshTextures;
    uint64 m_totalVert = 0;
    uint64 m_totalIndex = 0;
    String m_name;

  };
}
