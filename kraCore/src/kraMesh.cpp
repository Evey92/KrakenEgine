#include "kraMesh.h"
#include "kraTexture.h"
#include "kraGraphicsAPI.h"

namespace kraEngineSDK {

  Mesh::Mesh(Device& pDevice) {

    m_vertexBurffer = pDevice.createVertexBufferInstance();
    m_indexBuffer = pDevice.createIndexBufferInstance();
    m_diffuse = pDevice.createTextureInstance();
    m_normal = pDevice.createTextureInstance();
    m_specular = pDevice.createTextureInstance();
    m_metalness = pDevice.createTextureInstance();
    m_roughness = pDevice.createTextureInstance();
    m_emissive = pDevice.createTextureInstance();
    m_ambientOcclusion = pDevice.createTextureInstance();

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

    Vector<ShrdPtr<Texture>>::iterator it = m_meshTextures.begin();

    m_vertexBurffer->setVertexBuffer(*pDevice);
    m_indexBuffer->setIndexBuffer(*pDevice);

    if (m_diffuse != nullptr)
    {
      m_diffuse->setTextureShaderResource(pDevice, 0, 1);
    }
  /*  else
    {
      m_diffuse->createTexture2DFromFile(*pDevice,
                                         "resources/Textures/missingChecker.png",
                                         GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT,
                                         GFX_USAGE::E::kUSAGE_DEFAULT,
                                         CPU_USAGE::E::kCPU_ACCESS_WRITE, 
                                         0U);

      m_diffuse->setTextureShaderResource(pDevice, 0, 1);

    }*/
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

  Vector<ShrdPtr<Texture>>& const
  Mesh::getTextureVector() {
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