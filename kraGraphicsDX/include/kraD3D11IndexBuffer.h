#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"

namespace kraEngineSDK {

  template<typename ITYPE>
  class IndexBuffer : public GraphicsBuffer
  {
   public:
     IndexBuffer() = default;

    void 
    reserve(size_t numObjects)
    {
      m_indexData.reserve(numObjects);
    }

    void
    add(const ITYPE& vertex)
    {
      m_indexData.push_back(vertex);
    }

    void
    add(const std::vector<ITYPE>& vertices)
    {
      m_indexData.insert(m_indexData.end(), vertices.begin(), vertices.end());
    }

    void
    add(const ITYPE* pVertices, size_t numVertices)
    {
      m_indexData.insert(m_indexData.end(), pVertices, pVertices + numVertices);
    }

    void
    clear()
    {
      m_indexData.clear();
    }

    void 
    createHardwareBuffer(ID3D11Device* pDevice,
      D3D11_USAGE usage = D3D11_USAGE_DEFAULT) {
      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = usage;
      bd.ByteWidth = static_cast<uint32>(sizeof(ITYPE)* m_indexData.size());
      bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      InitData.pSysMem = &m_indexData[0];

      HRESULT hr = pDevice->CreateBuffer(&bd, &InitData, &m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Index Buffer.");
      }
    }

    void
    setIndexBuffer(ID3D11DeviceContext* pImmediateContext) {
      pImmediateContext->IASetIndexBuffer(m_pBuffer, DXGI_FORMAT_R16_UINT, 0);
    }

    void
      cleanIndexBuffer() {

    }

   private:
    std::vector<ITYPE> m_indexData;
       
  };
}
