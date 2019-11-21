#include "kraMesh.h"
#include "kraTexture.h"
#include "kraGraphicsAPI.h"

namespace kraEngineSDK {

  CLASS_DEFINITION(Component, Mesh)

  Mesh::Mesh(Device& pDevice, const ShrdPtr<GameObject>& owner)  :
  Component(owner) {
    
    //m_vertexBurffer = GraphicsAPI::instance().getDevice()->createVertexBufferInstance();
    m_vertexBurffer = pDevice.createVertexBufferInstance();
    m_indexBuffer = pDevice.createIndexBufferInstance();
    m_owner = owner;
  }


  void 
  Mesh::initialize(Device& pDevice)
  {
    m_owner->addComponent<Material>(m_owner);
    m_material = make_shared<Material>(m_owner->getComponent<Material>());
    
    m_material->initialize(pDevice);
    m_owner->getComponent<Material>().initialize(pDevice);
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
    
    //TODO: Fix this horrible mess. It's probably something stupid simple that I'm too tired to see

    //m_material->getAlbedoTex()->setTextureShaderResource(pDevice, 0, 1);
    m_owner->getComponent<Material>().getAlbedoTex()->setTextureShaderResource(pDevice, 0, 1);

    if (m_material->getNormalTex() != nullptr)
    {
      //m_material->getNormalTex()->setTextureShaderResource(pDevice, 1, 1);
      m_owner->getComponent<Material>().getNormalTex()->setTextureShaderResource(pDevice, 0, 1);
    }
    
    if (m_material->getMetalTex() != nullptr)
    {
      //m_material->getMetalTex()->setTextureShaderResource(pDevice, 2, 1);
      m_owner->getComponent<Material>().getMetalTex()->setTextureShaderResource(pDevice, 0, 1);

    }
    
    if (m_material->getRoughnessTex() != nullptr)
    {
      //m_material->getRoughnessTex()->setTextureShaderResource(pDevice, 3, 1);
      m_owner->getComponent<Material>().getRoughnessTex()->setTextureShaderResource(pDevice, 0, 1);

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

  const Vector<ShrdPtr<Texture>>&
  Mesh::getTextures() {
    return m_meshTextures;
  }

  void
  Mesh::setTexture(Device* pDevice, TEXTURE_TYPE::E texType, const ShrdPtr<Texture>& newTex) {

    if (texType == TEXTURE_TYPE::E::ALBEDO)
    {
      m_material->setAlbedoTex(*pDevice, newTex);
    }
    else if (texType == TEXTURE_TYPE::E::NORMAL)
    {
      m_material->setNormalTex(*pDevice, newTex);
    }
    else if (texType == TEXTURE_TYPE::E::METALNESS)
    {
      m_material->setMetalTex(*pDevice, newTex);
    }
    else if (texType == TEXTURE_TYPE::E::ROUGHNESS)
    {
      m_material->setRoughnessTex(*pDevice, newTex);
    }
    else if (texType == TEXTURE_TYPE::E::SPECULAR)
    {
      //TODO: Change it to set specular
      m_material->setAlbedoTex(*pDevice, newTex);
    }
    else if (texType == TEXTURE_TYPE::E::EMISSIVE)
    {
      //TODO: Change it to ser emmisive
      m_material->setAlbedoTex(*pDevice, newTex);
    }

  }


  void 
  Mesh::setMeshMaterial(Device* pDevice, Material* mat)
  {
    m_material->setAlbedoTex(*pDevice, mat->getAlbedoTex());
    m_material->setNormalTex(*pDevice, mat->getNormalTex());
    m_material->setMetalTex(*pDevice, mat->getMetalTex());
    m_material->setRoughnessTex(*pDevice, mat->getRoughnessTex());

  }

  void Mesh::setMaterialAlbedo(Device* pDevice, const ShrdPtr<Texture>& newTex)
  {
    m_owner->getComponent<Material>().setAlbedoTex(*pDevice, newTex);
  }

  ShrdPtr<Texture>
  Mesh::getTexture(TEXTURE_TYPE::E texType) {
    
    if (texType == TEXTURE_TYPE::E::ALBEDO)
    {
      return m_material->getAlbedoTex();
    }
    else if (texType == TEXTURE_TYPE::E::NORMAL)
    {
      return m_material->getNormalTex();
    }
    else if (texType == TEXTURE_TYPE::E::METALNESS)
    {
      return m_material->getMetalTex();
    }
    else if (texType == TEXTURE_TYPE::E::ROUGHNESS)
    {
      return m_material->getRoughnessTex();
    }
    /*else if (texType == TEXTURE_TYPE::E::SPECULAR)
    {
      return m_specular;
    }
    else if (texType == TEXTURE_TYPE::E::EMISSIVE)
    {
      return m_emissive;
    }*/
    return nullptr;
  }

  void Mesh::setName(String name)
  {
    m_name = name;
  }

  String 
  Mesh::getName()
  {
    return m_name;
  }

}