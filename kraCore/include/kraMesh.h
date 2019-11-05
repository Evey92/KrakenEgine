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
    initialize();

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
    setTexture(TEXTURE_TYPE::E texType, ShrdPtr<Texture> newTex);

    void
    setMeshMaterial(Material* mat);

    ShrdPtr<Texture> const
    getTexture(TEXTURE_TYPE::E texType);

    
  private:
    Material m_material = nullptr;
    IndexBuffer* m_indexBuffer = nullptr;
    VertexBuffer* m_vertexBurffer = nullptr;
    Vector<ShrdPtr<Texture>> m_meshTextures;
    ShrdPtr<Texture> m_diffuse = nullptr;
    ShrdPtr<Texture> m_normal = nullptr;
    ShrdPtr<Texture> m_specular = nullptr;
    ShrdPtr<Texture> m_metalness = nullptr;
    ShrdPtr<Texture> m_roughness = nullptr;
    ShrdPtr<Texture> m_emissive = nullptr;
    ShrdPtr<Texture> m_ambientOcclusion = nullptr;

  };
}
