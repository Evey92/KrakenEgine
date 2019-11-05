#include "kraMesh.h"
#include "kraTexture.h"
#include "kraGraphicsAPI.h"

namespace kraEngineSDK {

  CLASS_DEFINITION(Component, Mesh)

  Mesh::Mesh(Device& pDevice, GameObject* owner)  :
  Component(owner) {
    
    m_vertexBurffer = pDevice.createVertexBufferInstance();
    m_indexBuffer = pDevice.createIndexBufferInstance();
    m_diffuse = pDevice.createTextureInstance();
    m_normal = pDevice.createTextureInstance();
    m_specular = pDevice.createTextureInstance();
    m_metalness = pDevice.createTextureInstance();
    m_roughness = pDevice.createTextureInstance();
    m_emissive = pDevice.createTextureInstance();
    m_ambientOcclusion = pDevice.createTextureInstance();
    m_owner = owner;
  }


  void 
  Mesh::initialize()
  {
    m_owner->addComponent<Material>(m_owner);
    m_material = m_owner->getComponent<Material>();
    m_material.initialize();
  }

  void
  Mesh::initBuffers(std::vector<Vertex> vertices, std::vector<uint32> indices)
  {
    m_vertexBurffer->add(vertices);
    m_indexBuffer->add(indices);
  }

  void
  Mesh::DrawMesh(Device* pDevice) {
    
    m_vertexBurffer->setVertexBuffer(*pDevice);
    m_indexBuffer->setIndexBuffer(*pDevice);
    
    .m_material.getAlbedoTex()->setTextureShaderResource(pDevice, 0, 1);

    if (m_material.getNormalTex() != nullptr)
    {
      m_material.getNormalTex()->setTextureShaderResource(pDevice, 1, 1);
    }
    
    if (m_material.getMetalTex() != nullptr)
    {
      m_material.getMetalTex()->setTextureShaderResource(pDevice, 2, 1);
    }
    
    if (m_roughness != nullptr)
    {
      m_roughness->setTextureShaderResource(pDevice, 3, 1);
    }

    pDevice->DrawIndexed(m_indexBuffer->getBufferSize(), 0, 0);
  }

  IndexBuffer*
  Mesh::getIndexBuffer() {
    return m_indexBuffer;
  }

  VertexBuffer*
  Mesh::getVertexBuffer() {
    return m_vertexBurffer;
  }

  Vector<ShrdPtr<Texture>>& const
  Mesh::getTextures() {
    return m_meshTextures;
  }

  void
  Mesh::setTexture(TEXTURE_TYPE::E texType, ShrdPtr<Texture> newTex) {

    if (texType == TEXTURE_TYPE::E::BASECOLOR)
    {
      m_diffuse = newTex;
    }
    else if (texType == TEXTURE_TYPE::E::NORMAL)
    {
      m_normal = newTex;
    }
    else if (texType == TEXTURE_TYPE::E::SPECULAR)
    {
      m_specular = newTex;
    }
    else if (texType == TEXTURE_TYPE::E::ROUGHNESS)
    {
      m_roughness = newTex;
    }
    else if (texType == TEXTURE_TYPE::E::METALNESS)
    {
      m_metalness = newTex;
    }
    else if (texType == TEXTURE_TYPE::E::EMISSIVE)
    {
      m_emissive = newTex;
    }

  }


  void 
  Mesh::setMeshMaterial(Material* mat)
  {
    m_material.setAlbedoTex(GraphicsAPI::instance()->getDevice(), mat->getAlbedoTex());
    m_material.setNormalTex();
    m_material.setMetalTex();
    m_material.setRoughnessTex();
  }

  ShrdPtr<Texture> const
  Mesh::getTexture(TEXTURE_TYPE::E texType) {
    
    if (texType == TEXTURE_TYPE::E::BASECOLOR)
    {
      return m_diffuse;
    }
    else if (texType == TEXTURE_TYPE::E::NORMAL)
    {
      return m_normal;
    }
    else if (texType == TEXTURE_TYPE::E::SPECULAR)
    {
      return m_specular;
    }
    else if (texType == TEXTURE_TYPE::E::ROUGHNESS)
    {
      return m_roughness;
    }
    else if (texType == TEXTURE_TYPE::E::METALNESS)
    {
      return m_metalness;
    }
    else if (texType == TEXTURE_TYPE::E::EMISSIVE)
    {
      return m_emissive;
    }
    return nullptr;
  }

}