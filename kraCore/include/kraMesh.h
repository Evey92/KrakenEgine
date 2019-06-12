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
    
    IndexBuffer*
    getIndexBuffer();

    VertexBuffer*
    getVertexBuffer();

    Vector<Texture*>& const
    getTextureVector();

    Texture& const
    getDiffuseTextur();

    Texture& const
    getNormalTexture();

    Texture& const
    getSpecularTexture();

    Vector<Texture*>& const
    getMetalnessTexture();

    Texture& const
    getRoughnessTexture();

    Texture& const
    getEmissiveTexture();

    Texture& const
    getAmbientTexture();
    
  private:
    IndexBuffer* m_indexBuffer = nullptr;
    VertexBuffer* m_vertexBurffer = nullptr;
    Vector<Texture*> m_meshTextures;
    Texture* m_diffuse = nullptr;
    Texture* m_normal = nullptr;
    Texture* m_specular = nullptr;
    Texture* m_metalness = nullptr;
    Texture* m_roughness = nullptr;
    Material* m_emissive = nullptr;
    Material* m_ambientOcclusion = nullptr;

  };
}
