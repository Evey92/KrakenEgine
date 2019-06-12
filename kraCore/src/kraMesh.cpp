#include "kraMesh.h"
#include "kraTexture.h"

namespace kraEngineSDK {

  Mesh::Mesh(Device& pDevice) {

    m_vertexBurffer = pDevice.createVertexBufferInstance();
    m_indexBuffer = pDevice.createIndexBufferInstance();
    m_material = new Material(pDevice);

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

    for (it = m_meshTextures.begin(); it != m_meshTextures.end(); ++it)
    {
      (*it)->setTextureShaderResource(pDevice, 0, 1);
    }
    pDevice->DrawIndexed(m_indexBuffer->getBufferSize(), 0, 0);
  }

  Material&
  Mesh::getMaterial() {
    return *m_material;
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

}