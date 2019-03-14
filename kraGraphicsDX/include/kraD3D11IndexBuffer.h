#pragma once
#include <kraDevice.h>
#include <kraIndexBuffer.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {

  //template<typename ITYPE>
  class KRA_UTILGFX_EXPORT IndexBufferDX : 
    public GraphicsBufferDX, public IndexBuffer
  {
   public:
     IndexBufferDX() = default;
     ~IndexBufferDX() {}

     void 
    reserve(size_t numObjects)
    {
      m_indexData.reserve(numObjects);
    }

    void
    add(const uint32& vertex)
    {
      m_indexData.push_back(vertex);
    }

    void
    add(const std::vector<uint32>& vertices)
    {
      m_indexData.insert(m_indexData.end(), vertices.begin(), vertices.end());
    }

    void
    add(const uint32* pVertices, size_t numVertices)
    {
      m_indexData.insert(m_indexData.end(), pVertices, pVertices + numVertices);
    }

    void
    clear()
    {
      m_indexData.clear();
    }

    void
    Release() {
      m_pBuffer->Release();
    }

    void 
      createIndexBuffer(const Device& pDevice) {

      const DeviceDX& m_pDevice = reinterpret_cast<const DeviceDX&>(pDevice);
      
      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = D3D11_USAGE_DEFAULT;
      bd.ByteWidth = static_cast<uint32>(sizeof(uint32)* m_indexData.size());
      bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      InitData.pSysMem = &m_indexData[0];

      HRESULT hr = m_pDevice.m_pd3dDevice->CreateBuffer(&bd, &InitData, &m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Index Buffer.");
      }
    }

    void
    setIndexBuffer(const Device& pDevice) {
      const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

      m_device.m_pImmediateContext->IASetIndexBuffer(m_pBuffer, DXGI_FORMAT_R16_UINT, 0);
    }

    uint32
    getBufferSize() {
      return m_indexData.size();
    }

   private:
    std::vector<uint32> m_indexData;
       
  };
}
