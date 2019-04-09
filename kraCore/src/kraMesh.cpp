#include "kraMesh.h"

namespace kraEngineSDK {

  Mesh::Mesh(Device& pDevice){

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

    m_vertexBurffer->setVertexBuffer(*pDevice);
    m_indexBuffer->setIndexBuffer(*pDevice);
    pDevice->DrawIndexed(m_indexBuffer->getBufferSize(), 0, 0);
  }

  Material&
  Mesh::getMaterial() {
    return *m_material;
  }
}