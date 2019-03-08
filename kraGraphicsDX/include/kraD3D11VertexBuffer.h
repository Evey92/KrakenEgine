#pragma once
#include <d3d11.h>
#include <vector>
#include <kraDevice.h>
#include <kraVertexBuffer.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {

  //template<typename TVERTEX>
  class KRA_UTILGFX_EXPORT VertexBufferDX : 
    public GraphicsBufferDX, public VertexBuffer
  {
  public:
    VertexBufferDX() = default;
    ~VertexBufferDX() {}

    void
    reserve(size_t numObjects) {
      m_vertexData.reserve(numObjects);
    }

    void
    add(const Vertex& vertex) {
      m_vertexData.push_back(vertex);
    }

    void
    add(const std::vector<Vertex>& vertices) {
      m_vertexData.insert(m_vertexData.end(), vertices.begin(), vertices.end());
    }

    void
    add(const Vertex* pVertices, size_t numVertices) {
      m_vertexData.insert(m_vertexData.end(), pVertices, pVertices + numVertices);
    }

    void
    clear() {
      m_vertexData.clear();
    }

    void
    Release() {
      m_pBuffer->Release();
    }

    void
    createHardwareBuffer(Device* pDevice)
    {

      DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
      //D3D11_USAGE m_usage = usage;

      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = D3D11_USAGE_DEFAULT;
      bd.ByteWidth = static_cast<uint32>(sizeof(Vertex)* m_vertexData.size());
      bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      InitData.pSysMem = &m_vertexData[0];

      HRESULT hr = m_pDevice->m_pd3dDevice->CreateBuffer(&bd, &InitData, &m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Vertex Buffer.");
      }
    }

    void
      setVertexBuffer(Device* pImmediateContext)
    {
      DeviceDX* m_pDevice = static_cast<DeviceDX*>(pImmediateContext);

      uint32 stride = sizeof(Vertex);
      uint32 offset = 0;
      m_pDevice->m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pBuffer, &stride, &offset);
    }


   private:
    std::vector<Vertex> m_vertexData;
  };
}
