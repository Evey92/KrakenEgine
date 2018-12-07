#pragma once
#include "kraD3D11GraphicsBuffer.h"

namespace kraEngineSDK {

  template<typename CONSVERTEX>
  class  ConstantBuffer : public  GraphicsBuffer
  {
  public:
    ConstantBuffer() = default;
    

    void reserve(size_t numObjects)
    {
      m_constData.reserve(numObjects);
    }

    void add(const CONSVERTEX& vertex)
    {
      m_constData.push_back(vertex);
    }

    void add(const std::vector<CONSVERTEX>& vertices)
    {
      m_constData.insert(m_constData.end(), vertices.begin(), vertices.end());
    }

    void add(const CONSVERTEX* pVertices, size_t numVertices)
    {
      m_constData.insert(m_constData.end(), pVertices, pVertices + numVertices);
    }

    void clear()
    {
      m_constData.clear();
    }

    void createHardwareBuffer(ID3D11Device* pDevice, D3D11_USAGE usage = D3D11_USAGE_DEFAULT)
    {
      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = usage;
      bd.ByteWidth = static_cast<uint32>(sizeof(CONSVERTEX));
      bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      //InitData.pSysMem = &m_constData[0];

      HRESULT hr = pDevice->CreateBuffer(&bd, NULL ,&m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Constant Buffer).");
      }
    }

  private:
    std::vector<CONSVERTEX> m_constData;
  };
}
