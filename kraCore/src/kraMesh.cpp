#include "kraMesh.h"
#include "kraTexture.h"

namespace kraEngineSDK {

  Mesh::Mesh(Device& pDevice) {

    m_vertexBurffer = pDevice.createVertexBufferInstance();
    m_indexBuffer = pDevice.createIndexBufferInstance();

  }


  Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices) {
    m_vertexBurffer->add(vertices);
    m_indexBuffer->add(indices);
  }

  Mesh::Mesh(const Mesh& copyuMesh) {
    m_indexBuffer = copyuMesh.m_indexBuffer;
    m_vertexBurffer = copyuMesh.m_vertexBurffer;
  }

  void
  Mesh::DrawMesh(Device* pDevice) {

    Vector<Texture*>::iterator it = m_meshTextures.begin();

    m_vertexBurffer->setVertexBuffer(*pDevice);
    m_indexBuffer->setIndexBuffer(*pDevice);

    if (m_diffuse != nullptr)
    {
      m_diffuse->setTextureShaderResource(pDevice, 0, 1);
    }
    if (m_normal != nullptr)
    {
      m_normal->setTextureShaderResource(pDevice, 1, 1);
    }
    if (m_specular != nullptr)
    {
      m_normal->setTextureShaderResource(pDevice, 2, 1);
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

  Vector<Texture*>& const
  Mesh::getTextureVector() {
    return m_meshTextures;
  }

  void
  Mesh::setTexture(kraTextureType::E texType, ShrdPtr<Texture> newTex) {

    if (texType == kraTextureType::BASECOLOR)
    {
      m_diffuse = newTex;
    }
    else if (texType == kraTextureType::NORMAL)
    {
      m_normal = newTex;
    }
    else if (texType == kraTextureType::SPECULAR)
    {
      m_specular = newTex;
    }
    else if (texType == kraTextureType::ROUGHNESS)
    {
      m_roughness = newTex;
    }
    else if (texType == kraTextureType::METALNESS)
    {
      m_metalness = newTex;
    }
    else if (texType == kraTextureType::EMISSIVE)
    {
      m_emissive = newTex;
    }

  }


  ShrdPtr<Texture> const
  Mesh::getTexture(kraTextureType::E texType) {
    
    if (texType == kraTextureType::BASECOLOR)
    {
      return m_diffuse;
    }
    else if (texType == kraTextureType::NORMAL)
    {
      return m_normal;
    }
    else if (texType == kraTextureType::SPECULAR)
    {
      return m_specular;
    }
    else if (texType == kraTextureType::ROUGHNESS)
    {
      return m_roughness;
    }
    else if (texType == kraTextureType::METALNESS)
    {
      return m_metalness;
    }
    else if (texType == kraTextureType::EMISSIVE)
    {
      return m_emissive;
    }
  }

}