#pragma once
#include <d3d11.h>
#include <vector>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"


namespace kraEngineSDK {

  template<typename TVERTEX>
  class KRA_UTILGFX_EXPORT VertexBufferDX : public GraphicsBufferDX
  {
  public:
    VertexBufferDX() = default;
    ~VertexBufferDX() {}

    void
      reserve(size_t numObjects) {
      m_vertexData.reserve(numObjects);
    }

    void
      add(const TVERTEX& vertex) {
      m_vertexData.push_back(vertex);
    }

    void
      add(const std::vector<TVERTEX>& vertices) {
      m_vertexData.insert(m_vertexData.end(), vertices.begin(), vertices.end());
    }

    void
      add(const TVERTEX* pVertices, size_t numVertices) {
      m_vertexData.insert(m_vertexData.end(), pVertices, pVertices + numVertices);
    }

    void
      clear() {
      m_vertexData.clear();
    }

    void
      createHardwareBuffer(void* pDevice)
    {

      ID3D11Device* m_pDevice = reinterpret_cast<ID3D11Device*>(pDevice);
      //D3D11_USAGE m_usage = usage;

      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = D3D11_USAGE_DEFAULT;
      bd.ByteWidth = static_cast<uint32>(sizeof(TVERTEX)* m_vertexData.size());
      bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      InitData.pSysMem = &m_vertexData[0];

      HRESULT hr = m_pDevice->CreateBuffer(&bd, &InitData, &m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Vertex Buffer.");
      }
    }

    void
      setVertexBuffer(void* pImmediateContext)
    {
      ID3D11DeviceContext* m_immediatecontext = reinterpret_cast<ID3D11DeviceContext*>(pImmediateContext);

      uint32 stride = sizeof(TVERTEX);
      uint32 offset = 0;
      m_immediatecontext->IASetVertexBuffers(0, 1, &m_pBuffer, &stride, &offset);
    }

    void
    cleanVertexBuffer() {
      m_pBuffer->Release();
    }

   private:
    std::vector<TVERTEX> m_vertexData;
  };
}
