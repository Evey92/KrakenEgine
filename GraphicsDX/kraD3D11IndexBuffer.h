#pragma once
#include "kraD3D11GraphicsBuffer.h"

namespace kraEngineSDK {

  template<typename ITYPE>
  class kraD3D11IndexBuffer : public kraD3D11GraphicsBuffer
  {
   public:
    kraD3D11IndexBuffer();

    void 
    reserve(size_t numObjects)
    {
      m_indexData.reserve(numObjects);
    }

    void add(const ITYPE& vertex)
    {
      m_indexData.push_back(vertex);
    }

    void add(const vector<ITYPE>& vertices)
    {
      m_indexData.insert(m_indexData.end(), vertices.begin(), vertices.end())
    }

    void add(const ITYPE* pVertices, size_t numVertices)
    {
      m_indexData.insert(m_indexData.end(), pVertices, pVertices + numVertices)
    }

    void clear()
    {
      m_indexData.clear();
    }

    void createHardwareBuffer(ID3D11Device* pd3dDevice,
      unsigned int usage = D3D11_USAGE_DEFAULT) {
      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = usage;
      bd.ByteWidth = static_cast<uint32>(sizeof(ITYPE)* m_indexData.size());
      bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      InitData.pSysMem = &m_indexData[0];

      HRESULT hr = pd3dDevice->CreateBuffer(&bd, &InitData, &m_pBuffer);
      if (FAILED(hr))
      {
        throw exception("Failed to create Index Buffer.");
      }
    }

   private:
    vector<ITYPE> m_indexData;
       
  };
}
