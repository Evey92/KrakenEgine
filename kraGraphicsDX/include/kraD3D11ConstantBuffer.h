#pragma once
#include <kraConstantBuffer.h>
#include <kraDevice.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {

  template<typename CONSVERTEX>
  class KRA_UTILGFX_EXPORT  ConstantBufferDX : 
    public GraphicsBufferDX, public ConstantBuffer<CONSVERTEX>
  {
  public:
    ConstantBufferDX() = default;
    ~ConstantBufferDX() {}

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

    void
    Release() {

    }

    void createConstantBuffer(const Device& pDevice)
    {
      const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = D3D11_USAGE_DEFAULT;
      bd.ByteWidth = static_cast<uint32>(sizeof(CONSVERTEX));
      bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
      bd.CPUAccessFlags = 0;
    
      HRESULT hr = m_device.m_pd3dDevice->CreateBuffer(&bd, nullptr ,&m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Constant Buffer).");
      }
    }

    void
    setConstantBuffer(const Device& pDevice) {
      const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

    }

    void
    updateSubResources(const Device& pDevice, CBNeverChanges cbNvrMat) {
      
      const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

      m_device.m_pImmediateContext->UpdateSubresource(m_pBuffer, 0, nullptr, &cbNvrMat, 0, 0);
        
    }

    void
    updateSubResources(const Device& pDevice, CBChangeOnResize cbNvrMat) {

      const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

      m_device.m_pImmediateContext->UpdateSubresource(m_pBuffer, 0, nullptr, &cbNvrMat, 0, 0);

    }

    void
    updateSubResources(const Device& pDevice, CBChangesEveryFrame cbNvrMat) {

      const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

      m_device.m_pImmediateContext->UpdateSubresource(m_pBuffer, 0, nullptr, &cbNvrMat, 0, 0);
    }

    void
    setVertexConstantBuffer(const Device& pDevice, uint32 startSlot, uint32 NumBuffs) {
      const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

      m_device.m_pImmediateContext->VSSetConstantBuffers(startSlot, NumBuffs, &m_pBuffer);
      
    }

    void
    setPixelConstantBuffer(const Device& pDevice, uint32 startSlot, uint32 NumBuffs) {
      const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

      m_device.m_pImmediateContext->PSSetConstantBuffers(startSlot, NumBuffs, &m_pBuffer);

    }

  private:
    std::vector<CONSVERTEX> m_constData;
    ID3D11Buffer* m_pBuffer = nullptr;

  };
}
